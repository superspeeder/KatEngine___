#include <kat/base.hpp>
#include <iostream>


struct App {
    inline static kat::Engine::global_id_t s_globalID = 0;

    int v;

    explicit App(int v) : v(v) {}
};

struct Shit {
    int aaa;

    explicit Shit(int aaa) : aaa(aaa) {}
};


int main() {
    kat::run([&](const std::shared_ptr<kat::event::EngineConfigure>& event) {
        auto engine = event->engine;
        engine->emplaceGlobalSingletonShared<App>(7);
        std::cout << App::s_globalID << std::endl;
        std::cout << engine->getGlobal<std::shared_ptr<App>>()->v << std::endl;

        auto entity1 = kat::entityRegistry().create();
        auto entity2 = kat::entityRegistry().create();

        kat::entityRegistry().emplace<Shit>(entity1, 3);
        kat::entityRegistry().emplace<Shit>(entity2, 8);


        std::cout << "Entity1: " << (uint64_t)entity1 << "     aaa: " << kat::entityRegistry().get<Shit>(entity1).aaa << std::endl;
        std::cout << "Entity2: " << (uint64_t)entity2 << "     aaa: " << kat::entityRegistry().get<Shit>(entity2).aaa << std::endl;

    });
    return 0;
}
