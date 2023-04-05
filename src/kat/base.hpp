#pragma once

#include "fwd.hpp"
#include <tuple>

namespace kat {
    namespace {
        template<typename... T>
        using first_type_in_pack = std::tuple_element_t<0, std::tuple<T...> >;

        template<typename... T>
        static constexpr size_t pack_length = std::tuple_size_v<std::tuple<T...> >;

        template<class P>
        struct fproto_info;

        template<class R, class... Args>
        struct fproto_info<R(Args...)> {
            using ret = R;
            using args = std::tuple<Args...>;
        };

        template<class P, size_t i>
        using fproto_arg_t = std::tuple_element_t<i, typename fproto_info<P>::args>;

        template<class P>
        using fproto_ret_t = fproto_info<P>::ret;

        template<class P>
        constexpr size_t fproto_argc_v = std::tuple_size_v<typename fproto_info<P>::args>;

        template<typename T> struct shared_ptr_underlying;
        template<typename T> struct shared_ptr_underlying<std::shared_ptr<T>> { using type = T; };

        template<typename T>
        using shared_ptr_underlying_t = shared_ptr_underlying<T>::type;

        template<typename T>
        using remove_ref_cv = std::remove_cv_t<std::remove_reference_t<T>>;

        template<class P, typename base_event_t__>
        concept valid_listener_func_proto = std::same_as<fproto_ret_t<P>, void>
                && fproto_argc_v<P> == 1
                && std::derived_from<shared_ptr_underlying_t<remove_ref_cv<fproto_arg_t<P, 0> > >, base_event_t__>
                && std::is_reference_v<fproto_arg_t<P, 0> > == true
                && std::is_const_v<std::remove_reference_t<fproto_arg_t<P, 0> > > == true;


        template<typename L>
        using lambda_nc_ft = std::remove_pointer_t<decltype(+std::declval<L>())>;

        template<typename L, typename base_event_t__>
        concept valid_listener_func_nc_lambda = valid_listener_func_proto<lambda_nc_ft<L>, base_event_t__>;

        template<typename L>
        concept lambda_conv_fptr = std::is_function_v<lambda_nc_ft<L>>;

        static_assert(std::is_same_v<std::remove_cv_t<std::remove_reference_t<const std::shared_ptr<int>&> >, std::shared_ptr<int> >);

        using lt = decltype([](int) -> void{});
        static_assert(lambda_conv_fptr<lt> && std::same_as<int, fproto_arg_t<lambda_nc_ft<lt>, 0>>);

    }

    class EventManager {
    public:
        using event_t = std::type_index;
        using base_event_t = event::BaseEvent;
        using event_handler_prototype = void(const std::shared_ptr<base_event_t>&);
        using policies_t = eventpp::DefaultPolicies;

        using queue_t = eventpp::EventQueue<event_t, event_handler_prototype, policies_t>;

        template<std::derived_from<base_event_t> T>
        using typed_event_handler_prototype = void(const std::shared_ptr<T>&);

        template<std::derived_from<base_event_t> T, typename I>
        using typed_event_handler_prototype_member = void(I::*)(const std::shared_ptr<T>&);

        using handle_t = queue_t::Handle;



    private:

        queue_t m_Queue;



    public:

        template<typename L>
        inline handle_t addListener(L f)
        requires lambda_conv_fptr<L>
                && valid_listener_func_nc_lambda<L, base_event_t>
        {
            using P = lambda_nc_ft<L>;
            using T = shared_ptr_underlying_t<remove_ref_cv<fproto_arg_t<P, 0>>>;

            return m_Queue.appendListener(std::type_index(typeid(T)), [=](const std::shared_ptr<base_event_t>& e) {
                f(std::reinterpret_pointer_cast<T>(e));
            });
        };

        template<typename T, typename L>
        inline handle_t addListener(L f)
            requires std::is_invocable_r_v<void, L, const std::shared_ptr<T>&> && (!lambda_conv_fptr<L>)
        {
            return m_Queue.appendListener(std::type_index(typeid(T)), [=](const std::shared_ptr<base_event_t>& e) {
                f(std::reinterpret_pointer_cast<T>(e));
            });
        };

        template<typename P>
        inline handle_t addListener(std::function<P> f) requires valid_listener_func_proto<P, base_event_t> {
            using T = shared_ptr_underlying_t<remove_ref_cv<fproto_arg_t<P, 0>>>;

            return m_Queue.appendListener(std::type_index(typeid(T)), [f = std::move(f)](const std::shared_ptr<base_event_t>& e) {
                f(std::reinterpret_pointer_cast<T>(e));
            });
        };


        template<std::derived_from<base_event_t> T>
        inline handle_t addListener(typed_event_handler_prototype<T> f) {
            return m_Queue.appendListener(std::type_index(typeid(T)), [=](const std::shared_ptr<base_event_t>& e) {
                f(std::reinterpret_pointer_cast<T>(e));
            });
        };

        template<std::derived_from<base_event_t> T, typename I>
        inline handle_t addListener(typed_event_handler_prototype_member<T, I> f, I& i) {
            return m_Queue.appendListener(std::type_index(typeid(T)), [&](const std::shared_ptr<base_event_t>& e) {
                (i.*f)(std::reinterpret_pointer_cast<T>(e));
            });
        };

        template<std::derived_from<base_event_t> T, typename I>
        inline handle_t addListener(typed_event_handler_prototype_member<T, I> f, const std::shared_ptr<I>& i) {
            return m_Queue.appendListener(std::type_index(typeid(T)), [=](const std::shared_ptr<base_event_t>& e) {
                ((i.get())->*f)(std::reinterpret_pointer_cast<T>(e));
            });
        };

        template<std::derived_from<base_event_t> T>
        inline void post(const std::shared_ptr<T>& e) {
            m_Queue.enqueue(std::type_index(typeid(T)), e);
        };

        template<std::derived_from<base_event_t> T, typename... Args>
        inline void post(Args&&... args) {
            enqueue(std::make_shared<T>(std::forward(args)...));
        };

        template<std::derived_from<base_event_t> T>
        inline void dispatch(const std::shared_ptr<T>& e) {
            m_Queue.dispatch(std::type_index(typeid(T)), e);
        };

        template<std::derived_from<base_event_t> T, typename... Args>
        inline void dispatch(Args&&... args) {
            dispatch(std::make_shared<T>(std::forward<Args>(args)...));
        };

    };

    namespace {
        template<class T, typename global_id_t>
        concept singleton_global_class = std::same_as<decltype(T::s_globalID), global_id_t>;
    }

    class Engine : public std::enable_shared_from_this<Engine> {
    public:
        using global_id_t = uint64_t;

        static std::shared_ptr<Engine> create();

        ~Engine();

        [[nodiscard]] const std::unique_ptr<EventManager>& events() const;

        void mainloop();

        global_id_t addGlobal(const std::any& obj);
        void setGlobal(global_id_t id, const std::any& obj);

        const std::any& getGlobal(global_id_t id);

        template<typename T>
        inline T getGlobalTyped(global_id_t id) {
            return std::any_cast<T>(getGlobal(id));
        };

        template<singleton_global_class<global_id_t> T>
        inline T getGlobal() {
            return getGlobalTyped<T>(T::s_globalID);
        };

        template<class T> requires singleton_global_class<shared_ptr_underlying_t<T>, global_id_t>
        inline T getGlobal() {
            return getGlobalTyped<T>(shared_ptr_underlying_t<T>::s_globalID);
        };

        template<singleton_global_class<global_id_t> T, typename... Args>
        inline global_id_t emplaceGlobalSingleton(Args&&... args) {
            T o = T(std::forward<Args>(args)...);
            T::s_globalID = addGlobal(o);
            return T::s_globalID;
        };

        template<singleton_global_class<global_id_t> T, typename... Args>
        inline global_id_t emplaceGlobalSingletonShared(Args&&... args) {
            std::shared_ptr<T> o = std::make_shared<T>(std::forward<Args>(args)...);
            T::s_globalID = addGlobal(o);
            return T::s_globalID;
        };



    private:
        Engine();

        std::unique_ptr<EventManager> m_EventManager;

        std::unordered_map<global_id_t, std::any> m_Globals;
    };

    namespace event {
        struct EngineConfigure : public BaseEvent {
            explicit EngineConfigure(const std::shared_ptr<Engine> &engine);

            std::shared_ptr<Engine> engine;
        };
    }

    // Manage global state
    void init();
    void terminate();

    void run(std::function<EventManager::typed_event_handler_prototype<event::EngineConfigure> > f);

    template<typename I>
    inline void run(EventManager::typed_event_handler_prototype_member<event::EngineConfigure, I> f, I& i) {
        run([=](const std::unique_ptr<event::EngineConfigure>& e) {
            (i.*f)(e);
        });
    };


    template<typename I>
    inline void run(EventManager::typed_event_handler_prototype_member<event::EngineConfigure, I> f, I* i) {
        run([=](const std::unique_ptr<event::EngineConfigure>& e) {
            (i->*f)(e);
        });
    };


    template<typename I>
    inline void run(EventManager::typed_event_handler_prototype_member<event::EngineConfigure, I> f, const std::shared_ptr<I>& i) {
        run([=](const std::unique_ptr<event::EngineConfigure>& e) {
            ((i.get())->*f)(e);
        });
    };


    template<typename I>
    inline void run(EventManager::typed_event_handler_prototype_member<event::EngineConfigure, I> f, const std::unique_ptr<I>& i) {
        run([&](const std::unique_ptr<event::EngineConfigure>& e) {
            ((i.get())->*f)(e);
        });
    };


    const std::shared_ptr<Engine>& engine();
    const std::unique_ptr<EventManager>& events();
}