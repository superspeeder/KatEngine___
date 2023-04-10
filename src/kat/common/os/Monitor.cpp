#include "Monitor.hpp"
#include "kat/base.hpp"

namespace kat::os {
    void Monitor::refresh() {
        events()->dispatch<kat::event::os::RefreshMonitors>();
    }

    void Monitor::setup() {
        setupPlatform();
        refresh();
    }
} // kat::os