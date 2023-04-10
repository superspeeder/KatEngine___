#pragma once

#include "kat/common/os/Monitor.hpp"
#include "kat/fwd.hpp"
#include "kat/utils.hpp"

namespace kat::os::shared {

    class GLFWMonitor : public Monitor {
    public:

        [[nodiscard]] static const GLFWMonitor* get(GLFWmonitor* monitor);
        [[nodiscard]] static const GLFWMonitor* get(size_t monitor);
        [[nodiscard]] static const GLFWMonitor* primary();
        [[nodiscard]] static const GLFWMonitor* last();

        static inline const std::vector<GLFWMonitor*>& all() { return s_MonitorsByIndex; };

        static void reload();

        inline GLFWmonitor* handle() const noexcept { return m_Monitor; };

        std::string getName() override;

        size_t getIndex() const;

        static void installCallbacks();

    private:
        GLFWMonitor(GLFWmonitor *monitor, size_t index);

        static inline std::unordered_map<GLFWmonitor*, size_t> s_MonitorsByHandle;
        static inline std::vector<GLFWMonitor*> s_MonitorsByIndex;

        GLFWmonitor* m_Monitor;
        size_t m_Index;
    };

} // kat::os::shared
