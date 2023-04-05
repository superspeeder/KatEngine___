cmake_minimum_required(VERSION 3.24)
project(KatEngine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs)

add_library(KatEngine src/kat/base.cpp src/kat/base.hpp src/kat/fwd.hpp)
target_include_directories(KatEngine PUBLIC src/)
target_link_libraries(KatEngine PUBLIC glad::glad glm::glm glfw spdlog::spdlog eventpp::eventpp EnTT::EnTT)

add_library(KatEngine::KatEngine ALIAS KatEngine)

add_subdirectory(sample/)