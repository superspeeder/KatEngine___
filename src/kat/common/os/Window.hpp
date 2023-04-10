#pragma once

#include <variant>
#include <optional>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

#include "kat/common/data/CPUImage.hpp"
#include "kat/common/math/geometry.hpp"
#include "kat/fwd.hpp"

namespace kat {
    namespace os {
        enum class WindowMode {
            Windowed,
            FullscreenWindowed,
            Fullscreen
        };

        struct WindowedWindowMode {
            glm::uvec2 size;
        };

        struct WindowedFullscreenWindowMode {
            int monitor = 0;
        };

        struct FullscreenWindowMode {
            int monitor = 0;
            std::optional<glm::uvec2> resolutionOverride;
        };

        using WindowModeVariant = std::variant<WindowedWindowMode, WindowedFullscreenWindowMode, FullscreenWindowMode>;

        struct IconProperties {
            std::vector<std::shared_ptr<kat::CPUImage> > images;
        };

        enum class WindowFlagBits : uint8_t {
            eResizable      = 0b1,
            eVisible        = 0b10,
            eDecorated      = 0b100,
            eFloating       = 0b1000,
            eScaleToMonitor = 0b10000
        };

        using WindowFlags = uint8_t;

        constexpr WindowFlags operator|(const WindowFlagBits& a, const WindowFlagBits& b) {
            return static_cast<uint8_t>(a) | static_cast<uint8_t>(b);
        }

        constexpr WindowFlags operator|(const WindowFlags& a, const WindowFlagBits& b) {
            return a | static_cast<uint8_t>(b);
        }

        constexpr WindowFlags operator|(const WindowFlagBits& a, const WindowFlags& b) {
            return static_cast<uint8_t>(a) | b;
        }

        constexpr bool operator&(const WindowFlags& a, const WindowFlagBits& b) {
            return a & static_cast<uint8_t>(b);
        }

        constexpr WindowFlags operator^(const WindowFlags& a, const WindowFlagBits& b) {
            return a ^ static_cast<uint8_t>(b);
        }

        constexpr WindowFlags DEFAULT_WINDOW_FLAGS = WindowFlagBits::eResizable
                                                   | WindowFlagBits::eVisible
                                                   | WindowFlagBits::eDecorated;

        enum class StandardCursor {
            Arrow,
            IBeam,
            Crosshair,
            Hand,
            HResize,
            VResize
        };

        struct CustomCursorProperties {
            std::shared_ptr<kat::CPUImage> image;
            glm::ivec2 hotspot;
        };

        using CursorPropertiesVariant = std::variant<StandardCursor, CustomCursorProperties>;

        enum class CursorMode {
            Normal,
            Hidden,
            Disabled
        };

        struct WindowProperties {
            WindowModeVariant windowMode = WindowedWindowMode{{800, 450}};
            std::string caption = "Window";
            std::optional<IconProperties> icon;

            WindowFlags windowFlags = DEFAULT_WINDOW_FLAGS;

            std::optional<std::pair<glm::uvec2, glm::uvec2>> sizeLimits;
            std::optional<std::pair<int,int>> aspectRatio;
            std::optional<CursorPropertiesVariant> cursor;
        };

        class Monitor;

        class Window : public std::enable_shared_from_this<Window> {
        public:
            virtual ~Window() = default;

            virtual void close() = 0;
            virtual void preventClose() = 0;

            [[nodiscard]] virtual bool isOpen() = 0;

            virtual void setSize(const glm::uvec2& size) = 0;
            virtual void setPosition(const glm::ivec2& pos) = 0;

            virtual void setSizeLimits(const std::pair<glm::uvec2, glm::uvec2>& limits) = 0;
            virtual void setSizeLimits(const glm::uvec2& minSize, const glm::uvec2& maxSize) = 0;

            virtual void disableSizeLimits() = 0;

            virtual void setAspectRatio(const std::pair<int, int>& ratio) = 0;
            virtual void setAspectRatio(int numer, int denom) = 0;
            virtual void unlockAspectRatio() = 0;

            [[nodiscard]] virtual glm::ivec2 getPosition() = 0;
            [[nodiscard]] virtual glm::uvec2 getSize() = 0;

            virtual void setTitle(const std::string& title) = 0;

            virtual void setIcon(const IconProperties& icon) = 0;

            [[nodiscard]] virtual glm::uvec2 getFramebufferSize() = 0;
            [[nodiscard]] virtual math::Rect<int> getFrameSize() = 0;

            [[nodiscard]] virtual glm::vec2 getContentScale() = 0;

            [[nodiscard]] virtual float getOpacity() = 0;
            virtual void setOpacity(float opacity) = 0;

            virtual void iconify() = 0;

            virtual void maximize() = 0;

            virtual void restore() = 0;

            virtual void show() = 0;

            virtual void hide() = 0;

            virtual void focus() = 0;

            virtual void requestAttention() = 0;

            [[nodiscard]] virtual const Monitor * getMonitor() = 0;

            virtual void setWindowMode(WindowModeVariant windowMode) = 0;

            [[nodiscard]] virtual WindowModeVariant getWindowMode() = 0;

            [[nodiscard]] virtual bool isFocused() = 0;
            [[nodiscard]] virtual bool isHovered() = 0;
            [[nodiscard]] virtual bool isMaximized() = 0;
            [[nodiscard]] virtual bool isIconified() = 0;

            virtual void setFloating(bool floating) = 0;
            virtual void setDecorated(bool decorated) = 0;

            virtual void setCursorMode(const CursorMode& mode) = 0;
            [[nodiscard]] virtual CursorMode getCursorMode() = 0;

            virtual void setCursor(const CursorPropertiesVariant& cursor) = 0;
        };

    } // os

    namespace event::os {
        struct WindowEvent : public BaseEvent {
            explicit WindowEvent(const std::shared_ptr<kat::os::Window> &window);

            std::shared_ptr<kat::os::Window> window;
        };

        struct WindowCloseEvent : public WindowEvent {};
        struct WindowMovedEvent : public WindowEvent {
            WindowMovedEvent(const std::shared_ptr<kat::os::Window> &window, const glm::ivec2 &position);

            glm::ivec2 position;
        };

        struct WindowResizedEvent : public WindowEvent {
            WindowResizedEvent(const std::shared_ptr<kat::os::Window> &window, const glm::uvec2 &size);

            glm::uvec2 size;
        };

        struct WindowRefreshEvent : public WindowEvent {};

        struct WindowFocusEvent : public WindowEvent {};
        struct WindowUnfocusEvent : public WindowEvent {};

        struct WindowIconifyEvent : public WindowEvent {};

        struct WindowMaximizeEvent : public WindowEvent {};
        struct WindowRestoreEvent : public WindowEvent {
            enum class PreviousState {
                Iconified,
                Maximized
            };

            WindowRestoreEvent(const std::shared_ptr<kat::os::Window> &window, PreviousState previous_state);

            PreviousState previousState;
        };

        struct WindowFramebufferResizedEvent : public WindowEvent {

            WindowFramebufferResizedEvent(const std::shared_ptr<kat::os::Window> &window, const glm::uvec2 &size);

            glm::uvec2 size;
        };

        struct WindowContentScaleChangedEvent : public WindowEvent {
            WindowContentScaleChangedEvent(const std::shared_ptr<kat::os::Window> &window,
                                           const glm::vec2 &content_scale);

            glm::vec2 contentScale;
        };
    }
} // kat
