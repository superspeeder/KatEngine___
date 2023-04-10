cmake_minimum_required(VERSION 3.22)

add_subdirectory(glfw)
add_subdirectory(spdlog)
add_subdirectory(glm)
add_subdirectory(glad)
add_subdirectory(eventpp)
add_subdirectory(entt)

set(STB_ORIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stb)

add_subdirectory(stb_impl)