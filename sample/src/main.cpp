#include <kat/base.hpp>
#include <iostream>


struct App {
    inline static kat::Engine::global_id_t s_globalID = 0;

    int v;

    explicit App(int v) : v(v) {}
};


int main() {
    kat::run([&](const std::shared_ptr<kat::event::EngineConfigure>& event) {
        auto engine = event->engine;
        engine->emplaceGlobalSingletonShared<App>(7);
        std::cout << App::s_globalID << std::endl;
        std::cout << engine->getGlobal<std::shared_ptr<App>>()->v << std::endl;
    });
    return 0;
}
