#include <kat/base.hpp>
#include <iostream>


struct App {
    KAT_ENGINE_GLOBAL_SINGLETON;
};


int main() {
    kat::run([&](const std::shared_ptr<kat::event::EngineConfigure>& event) {
        event->engine->emplaceGlobalSingletonShared<App>();

        
    });
    return 0;
}
