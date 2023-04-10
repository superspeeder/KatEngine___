#include "GLFWMonitor.hpp"
#include "spdlog/spdlog.h"

namespace kat::os::shared {
    GLFWMonitor::GLFWMonitor(GLFWmonitor *monitor, size_t index) : m_Monitor(monitor), m_Index(index) {}

    const GLFWMonitor* GLFWMonitor::get(GLFWmonitor *monitor) {
        auto mon = s_MonitorsByHandle.find(monitor);
        if (mon == s_MonitorsByHandle.end()) {
            spdlog::critical("Invalid monitor handle passed to kat::os::shared::GLFWMonitor::get(GLFWmonitor*).");
            throw std::runtime_error("Invalid monitor handle passed to kat::os::shared::GLFWMonitor::get(GLFWmonitor*).");
        }
        return get(mon->second);
    }

    const GLFWMonitor* GLFWMonitor::get(size_t monitor) {
        if (monitor >= s_MonitorsByIndex.size()) {
            spdlog::warn("Monitor index {} is out of range. Defaulting to primary.", monitor);
            return primary();
        }

        return s_MonitorsByIndex[monitor];
    }

    const GLFWMonitor* GLFWMonitor::primary() {
        return s_MonitorsByIndex[0];
    }

    const GLFWMonitor* GLFWMonitor::last() {
        return s_MonitorsByIndex[s_MonitorsByIndex.size() - 1];
    }

    void GLFWMonitor::reload() {
        for (auto* ptr : s_MonitorsByIndex) {
            delete ptr;
        }

        s_MonitorsByIndex.clear();
        s_MonitorsByHandle.clear();

        int monitorCount;
        auto** monitors = glfwGetMonitors(&monitorCount);

        spdlog::info("{} monitors detected.", monitorCount);

        for (size_t idx = 0; idx < monitorCount; idx++) {
            auto m = monitors[idx];
            s_MonitorsByIndex.push_back(new GLFWMonitor(m, idx));
        }
    }

    std::string GLFWMonitor::getName() {
        return glfwGetMonitorName(m_Monitor);
    }

    size_t GLFWMonitor::getIndex() const {
        return m_Index;
    }

    void GLFWMonitor::installCallbacks() {
        glfwSetMonitorCallback(+[](GLFWmonitor*, int) {
            Monitor::refresh();
        });
    }
} // kat::os::shared