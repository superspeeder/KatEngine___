cmake_minimum_required(VERSION 3.24)

add_executable(KatEngine_Sample src/main.cpp)
target_include_directories(KatEngine_Sample PRIVATE src/)
target_link_libraries(KatEngine_Sample PRIVATE KatEngine::KatEngine)