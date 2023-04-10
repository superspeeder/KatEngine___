#pragma once
#ifdef WIN32

#define GLFW_EXPOSE_NATIVE_WIN32

#include "kat/fwd.hpp"
#include <GLFW/glfw3native.h>

#include "kat/common/os/shared/GLFWWindow.hpp"


namespace kat::os::windows {

    class WindowsMonitor {
    public:

        WindowsMonitor() = delete;
        ~WindowsMonitor() = delete;

        static void refresh();

        static Monitor* get(HMONITOR hMonitor);

    private:

        static inline std::unordered_map<HMONITOR, Monitor*> s_NativeReverseMapping;
        static inline std::unordered_map<std::string, HMONITOR> s_MonitorNameMap;
    };

} // windows
#endif