#pragma once
#include "kat/fwd.hpp"

namespace kat::os {

    class Monitor {
    public:

        virtual ~Monitor() = default;

        static void refresh();

        virtual std::string getName() = 0;

        static void setup();
        static void setupPlatform();

    private:


    };
} // kat::os


namespace kat::event::os {
    struct RefreshMonitors : public BaseEvent {};
}