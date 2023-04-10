#include "common.hpp"

#include "os/Monitor.hpp"
#include "os/Window.hpp"

namespace kat {
    void commonSetup() {
        os::Monitor::setup();
    }
}