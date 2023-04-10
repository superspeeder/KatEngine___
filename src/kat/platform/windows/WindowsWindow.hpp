#pragma once
#ifdef WIN32

#define GLFW_EXPOSE_NATIVE_WIN32

#include "kat/fwd.hpp"
#include <GLFW/glfw3native.h>

#include "kat/common/os/shared/GLFWWindow.hpp"

namespace kat {
    namespace os {
        namespace windows {

            class WindowsWindow : public kat::os::shared::GLFWWindow {

            public:
                const Monitor *getMonitor() override;
            };

        } // kat
    } // os
} // windows

#endif