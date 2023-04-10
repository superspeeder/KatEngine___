#ifdef WIN32
#include "WindowsWindow.hpp"
#include "WindowsMonitor.hpp"
#include <Windows.h>

namespace kat {
    namespace os {
        namespace windows {
            const Monitor *WindowsWindow::getMonitor() {
                HWND hwnd = glfwGetWin32Window(m_Window);
                HMONITOR hmonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
                return WindowsMonitor::get(hmonitor);
            }
        } // kat
    } // os
} // windows
#endif