cmake_minimum_required(VERSION 3.15)
project(glfwdemo)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
        hex_library
        GIT_REPOSITORY https://github.com/3vilM33pl3/hexgrpc.git
)
FetchContent_MakeAvailable(hex_library)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.2
)
FetchContent_MakeAvailable(glfw)

add_subdirectory(hexmap)
add_subdirectory(apps)
