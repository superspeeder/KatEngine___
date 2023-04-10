#ifdef WIN32
#include "WindowsMonitor.hpp"
#include "kat/base.hpp"

namespace kat::os::windows {
    void WindowsMonitor::refresh() {
        using namespace kat::os::shared;
        GLFWMonitor::reload();

        WindowsMonitor::s_NativeReverseMapping.clear();
        WindowsMonitor::s_MonitorNameMap.clear();

        EnumDisplayMonitors(nullptr, nullptr, +[](HMONITOR hMonitor, HDC hDC, LPRECT lpRect, LPARAM lParam) -> BOOL {
            MONITORINFOEX mInfo{};
            GetMonitorInfoA(hMonitor, &mInfo);

            std::string name = mInfo.szDevice;

            WindowsMonitor::s_MonitorNameMap[name] = hMonitor;

            return TRUE;
        }, NULL);

        for (auto* m : GLFWMonitor::all()) {
            std::string monitorName = glfwGetWin32Monitor(m->handle());
            WindowsMonitor::s_NativeReverseMapping[WindowsMonitor::s_MonitorNameMap[monitorName]] = m;
        }
    }

    Monitor *WindowsMonitor::get(HMONITOR hMonitor) {
        return s_NativeReverseMapping[hMonitor];
    }
} // windows

void kat::os::Monitor::setupPlatform() {
    kat::os::shared::GLFWMonitor::installCallbacks();
    kat::events()->addListener([](const std::shared_ptr<kat::event::os::RefreshMonitors>& event) {
        kat::os::windows::WindowsMonitor::refresh();
    });
}

#endif
