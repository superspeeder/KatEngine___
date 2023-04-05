#include "base.hpp"
#include <eventpp/utilities/argumentadapter.h>

namespace kat {

    std::shared_ptr<Engine> s_Engine;

    std::shared_ptr<Engine> Engine::create() {
        return std::shared_ptr<Engine>(new Engine());
    }

    Engine::Engine() : m_EventManager(std::make_unique<EventManager>()) {
        glfwInit();
    }

    Engine::~Engine() {
        glfwTerminate();
    }

    const std::unique_ptr<EventManager> &Engine::events() const {
        return m_EventManager;
    }

    void Engine::mainloop() {
        m_EventManager->dispatch<event::EngineConfigure>(shared_from_this());
    }

    using distrib_t = std::uniform_int_distribution<Engine::global_id_t>;
    distrib_t distribution{};
    std::random_device rd;
    std::mt19937_64 gen(rd());


    Engine::global_id_t Engine::addGlobal(const std::any &obj) {
        global_id_t id = distribution(gen);
        while (m_Globals.contains(id)) {
            id = distribution(gen); // Keep generating id's until there isn't a collision.
        }

        setGlobal(id, obj);

        return id;
    }

    void Engine::setGlobal(Engine::global_id_t id, const std::any &obj) {
        m_Globals[id] = obj;
    }

    const std::any &Engine::getGlobal(Engine::global_id_t id) {
        return m_Globals[id];
    }

    void init() {
        s_Engine = Engine::create();
    }

    void terminate() {
        s_Engine.reset();
    }

    const std::shared_ptr<Engine> &engine() {
        return s_Engine;
    }

    const std::unique_ptr<EventManager> &events() {
        return s_Engine->events();
    }

    event::EngineConfigure::EngineConfigure(const std::shared_ptr<Engine> &engine) : engine(engine) {}

    void run(std::function<EventManager::typed_event_handler_prototype<event::EngineConfigure> > f) {
        init();
        events()->addListener(std::move(f));

        s_Engine->mainloop();

        terminate();
    }

}