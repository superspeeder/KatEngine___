cmake_minimum_required(VERSION 3.8)

set(STB_HEADERS ${STB_ORIG_DIR}/stb_image.h ${STB_ORIG_DIR}/stb_truetype.h ${STB_ORIG_DIR}/stb_image_write.h)

set(STB_INCLUDE_DIR_PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include/)
file(REMOVE_RECURSE ${STB_INCLUDE_DIR_PUBLIC})
file(COPY ${STB_HEADERS} DESTINATION ${STB_INCLUDE_DIR_PUBLIC})

add_library(stb src/stb_image.cpp src/stb_image_write.cpp src/stb_truetype.cpp)

target_include_directories(stb PUBLIC ${STB_INCLUDE_DIR_PUBLIC})

add_custom_command(
        TARGET stb PRE_BUILD
        COMMAND_EXPAND_LISTS
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${STB_INCLUDE_DIR_PUBLIC}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${STB_HEADERS} ${STB_INCLUDE_DIR_PUBLIC}
)

add_library(stb::stb ALIAS stb)