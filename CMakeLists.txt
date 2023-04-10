cmake_minimum_required(VERSION 3.24)
project(KatEngine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs)

add_library(KatEngine src/kat/base.cpp src/kat/base.hpp src/kat/fwd.hpp src/kat/common/os/Window.cpp src/kat/common/os/Window.hpp src/kat/platform/wayland/WaylandWindow.cpp src/kat/platform/wayland/WaylandWindow.hpp src/kat/platform/windows/WindowsWindow.cpp src/kat/platform/windows/WindowsWindow.hpp src/kat/platform/x11/X11Window.cpp src/kat/platform/x11/X11Window.hpp src/kat/common/data/CPUImage.cpp src/kat/common/data/CPUImage.hpp src/kat/common/os/Input.cpp src/kat/common/os/Input.hpp src/kat/common/os/shared/GLFWWindow.cpp src/kat/common/os/shared/GLFWWindow.hpp src/kat/common/os/Monitor.cpp src/kat/common/os/Monitor.hpp src/kat/common/os/shared/GLFWMonitor.cpp src/kat/common/os/shared/GLFWMonitor.hpp src/kat/platform/windows/WindowsMonitor.cpp src/kat/platform/windows/WindowsMonitor.hpp src/kat/common/os/setup.cpp src/kat/common/common.cpp src/kat/common/common.hpp)
target_include_directories(KatEngine PUBLIC src/)
target_link_libraries(KatEngine PUBLIC glad::glad glm::glm glfw spdlog::spdlog eventpp::eventpp EnTT::EnTT stb::stb)

add_library(KatEngine::KatEngine ALIAS KatEngine)

add_subdirectory(sample/)