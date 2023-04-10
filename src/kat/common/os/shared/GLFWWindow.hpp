#pragma once

#include "kat/common/os/Window.hpp"
#include "kat/common/os/shared/GLFWMonitor.hpp"
#include "kat/fwd.hpp"

namespace kat::os::shared {

    /**
     * Shared base for glfw-based window implementations. Provides standard logic.
     */
    class GLFWWindow : public kat::os::Window {
    public:
        void close() override;

        void preventClose() override;

        bool isOpen() override;

        void setSize(const glm::uvec2 &size) override;

        void setPosition(const glm::ivec2 &pos) override;

        void setSizeLimits(const std::pair<glm::uvec2, glm::uvec2> &limits) override;

        void setSizeLimits(const glm::uvec2 &minSize, const glm::uvec2 &maxSize) override;

        void disableSizeLimits() override;

        void setAspectRatio(const std::pair<int, int> &ratio) override;

        void setAspectRatio(int numer, int denom) override;

        void unlockAspectRatio() override;

        glm::ivec2 getPosition() override;

        glm::uvec2 getSize() override;

        void setTitle(const std::string &title) override;

        void setIcon(const IconProperties &icon) override;

        glm::uvec2 getFramebufferSize() override;

        math::Rect<int> getFrameSize() override;

        glm::vec2 getContentScale() override;

        float getOpacity() override;

        void setOpacity(float opacity) override;

        void iconify() override;

        void maximize() override;

        void restore() override;

        void show() override;

        void hide() override;

        void focus() override;

        void requestAttention() override;

        void setWindowMode(WindowModeVariant windowMode) override;

        WindowModeVariant getWindowMode() override;

        bool isFocused() override;

        bool isHovered() override;

        bool isMaximized() override;

        bool isIconified() override;

        void setFloating(bool floating) override;

        void setDecorated(bool decorated) override;

        void setCursorMode(const CursorMode &mode) override;

        CursorMode getCursorMode() override;

    protected:
        GLFWwindow *m_Window;
    };

} // kat::os::shared
