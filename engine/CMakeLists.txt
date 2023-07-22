cmake_minimum_required(VERSION 3.24)
project(KatEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(KatEngine )
target_include_directories(KatEngine PUBLIC src/)
target_link_libraries(KatEngine PUBLIC glm::glm glfw spdlog::spdlog eventpp::eventpp EnTT::EnTT stb::stb)

add_library(KatEngine::KatEngine ALIAS KatEngine)