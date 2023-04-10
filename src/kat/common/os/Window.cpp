#include "Window.hpp"

namespace kat::event::os {
    WindowEvent::WindowEvent(const std::shared_ptr<kat::os::Window> &window) : window(window) {}

    WindowMovedEvent::WindowMovedEvent(const std::shared_ptr<kat::os::Window> &window, const glm::ivec2 &position)
            : WindowEvent(window), position(position) {}

    WindowResizedEvent::WindowResizedEvent(const std::shared_ptr<kat::os::Window> &window, const glm::uvec2 &size)
            : WindowEvent(window), size(size) {}

    WindowRestoreEvent::WindowRestoreEvent(const std::shared_ptr<kat::os::Window> &window,
                                           WindowRestoreEvent::PreviousState previous_state) : WindowEvent(window),
                                                                                               previousState(
                                                                                                       previous_state) {}

    WindowFramebufferResizedEvent::WindowFramebufferResizedEvent(const std::shared_ptr<kat::os::Window> &window,
                                                                 const glm::uvec2 &size) : WindowEvent(window),
                                                                                           size(size) {}

    WindowContentScaleChangedEvent::WindowContentScaleChangedEvent(const std::shared_ptr<kat::os::Window> &window,
                                                                   const glm::vec2 &content_scale) : WindowEvent(
            window), contentScale(content_scale) {}
}