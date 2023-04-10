#include "GLFWWindow.hpp"
#include "spdlog/spdlog.h"

namespace kat::os::shared {
    void GLFWWindow::close() {
        glfwSetWindowShouldClose(m_Window, true);
    }

    void GLFWWindow::preventClose() {
        glfwSetWindowShouldClose(m_Window, false);
    }

    bool GLFWWindow::isOpen() {
        return !glfwWindowShouldClose(m_Window);
    }

    void GLFWWindow::setSize(const glm::uvec2 &size) {
        glfwSetWindowSize(m_Window, size.x, size.y);
    }

    void GLFWWindow::setPosition(const glm::ivec2 &pos) {
        glfwSetWindowPos(m_Window, pos.x, pos.y);
    }

    void GLFWWindow::setSizeLimits(const std::pair<glm::uvec2, glm::uvec2> &limits) {
        setSizeLimits(limits.first, limits.second);
    }

    void GLFWWindow::setSizeLimits(const glm::uvec2 &minSize, const glm::uvec2 &maxSize) {
        glfwSetWindowSizeLimits(m_Window, minSize.x, minSize.y, maxSize.x, maxSize.y);
    }

    void GLFWWindow::disableSizeLimits() {
        glfwSetWindowSizeLimits(m_Window, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
    }

    void GLFWWindow::setAspectRatio(const std::pair<int, int> &ratio) {
        setAspectRatio(ratio.first, ratio.second);
    }

    void GLFWWindow::setAspectRatio(int numer, int denom) {
        glfwSetWindowAspectRatio(m_Window, numer, denom);
    }

    void GLFWWindow::unlockAspectRatio() {
        glfwSetWindowAspectRatio(m_Window, GLFW_DONT_CARE, GLFW_DONT_CARE);
    }

    glm::ivec2 GLFWWindow::getPosition() {
        glm::ivec2 v;
        glfwGetWindowPos(m_Window, &v.x, &v.y);
        return v;
    }

    glm::uvec2 GLFWWindow::getSize() {
        glm::ivec2 v;
        glfwGetWindowSize(m_Window, &v.x, &v.y);
        return v;
    }

    void GLFWWindow::setTitle(const std::string &title) {
        glfwSetWindowTitle(m_Window, title.c_str());
    }

    void GLFWWindow::setIcon(const IconProperties &icon) {
        std::vector<unsigned char*> bufs;
        std::vector<GLFWimage> images;
        for (const auto& image : icon.images) {
            auto size = image->getSize();
            if (image->getChannels() == 4 && size.x == size.y && size.x % 2 == 0) {

                auto* buf = static_cast<unsigned char *>(malloc(sizeof(unsigned char) * size.x * size.y));

                bufs.push_back(buf);
                images.push_back(GLFWimage{
                    static_cast<int>(size.x), static_cast<int>(size.y), buf
                });
            } else {
                spdlog::warn("Invalid Icon Image");
            }
        }

        glfwSetWindowIcon(m_Window, images.size(), images.data());

        for (unsigned char* buf : bufs) {
            free(buf);
        }
    }

    glm::uvec2 GLFWWindow::getFramebufferSize() {
        glm::ivec2 v;
        glfwGetFramebufferSize(m_Window, &v.x, &v.y);
        return v;
    }

    math::Rect<int> GLFWWindow::getFrameSize() {
        math::Rect<int> rect;
        glfwGetWindowFrameSize(m_Window, &rect.left, &rect.top, &rect.right, &rect.bottom);
        return rect;
    }

    glm::vec2 GLFWWindow::getContentScale() {
        glm::vec2 v;
        glfwGetWindowContentScale(m_Window, &v.x, &v.y);
        return v;
    }

    float GLFWWindow::getOpacity() {
        return glfwGetWindowOpacity(m_Window);
    }

    void GLFWWindow::setOpacity(float opacity) {
        glfwSetWindowOpacity(m_Window, opacity);
    }

    void GLFWWindow::iconify() {
        glfwIconifyWindow(m_Window);
    }

    void GLFWWindow::maximize() {
        glfwMaximizeWindow(m_Window);
    }

    void GLFWWindow::restore() {
        glfwRestoreWindow(m_Window);
    }

    void GLFWWindow::show() {
        glfwShowWindow(m_Window);
    }

    void GLFWWindow::hide() {
        glfwHideWindow(m_Window);
    }

    void GLFWWindow::focus() {
        glfwFocusWindow(m_Window);
    }

    void GLFWWindow::requestAttention() {
        glfwRequestWindowAttention(m_Window);
    }

    void GLFWWindow::setWindowMode(WindowModeVariant windowMode) {
        // TODO
    }

    WindowModeVariant GLFWWindow::getWindowMode() {
        return kat::os::WindowModeVariant();
    }

    bool GLFWWindow::isFocused() {
        return false;
    }

    bool GLFWWindow::isHovered() {
        return false;
    }

    bool GLFWWindow::isMaximized() {
        return false;
    }

    bool GLFWWindow::isIconified() {
        return false;
    }

    void GLFWWindow::setFloating(bool floating) {

    }

    void GLFWWindow::setDecorated(bool decorated) {

    }

    void GLFWWindow::setCursorMode(const CursorMode &mode) {

    }

    CursorMode GLFWWindow::getCursorMode() {
        return CursorMode::Hidden;
    }
} // kat::os::shared