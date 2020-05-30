cmake_minimum_required(VERSION 3.16)
#set(CMAKE_USER_MAKE_RULES_OVERRIDE
#        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/c_flags_overrides.cmake)
#set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
#        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cxx_flags_overrides.cmake)

project(hexmap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")

find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
        cli
        GIT_REPOSITORY  https://github.com/daniele77/cli.git
        GIT_TAG         v1.1.1
)
FetchContent_MakeAvailable(cli)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.2
)
FetchContent_MakeAvailable(glfw)

set(Boost_DEBUG OFF)
set(BUILD_TESTING OFF)
set(Boost_USE_MULTITHREADED ON)

IF (WIN32)
    #    Point to Boost by setting BOOST_ROOT variable
    #    cmake -DBOOST_ROOT=C:/local/boost_1_69_0
    #    set(BOOST_ROOT C:/local/boost_1_69_0)
    #    On the windows instance of Github Actions Boost is located here:
    #    cmake -DBOOST_ROOT=C:/hostedtoolcache/windows/Boost/1.69.0
    #    set(BOOST_ROOT C:/hostedtoolcache/windows/Boost/1.69.0)
    add_definitions(/D_WIN32_WINNT=0x0601)
    set(Boost_NO_SYSTEM_PATHS ON)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_COMPILER -vc141)
    set(Boost_ARCHITECTURE -x64)
    set(CMAKE_CXX_FLAGS "-I${CMAKE_CURRENT_LIST_DIR}/glad /EHsc")
ENDIF()

find_package(Boost REQUIRED COMPONENTS system atomic filesystem log exception)
include_directories(${Boost_INCLUDE_DIRS})

FetchContent_Declare(
        hex_client_lib
        GIT_REPOSITORY  https://github.com/3vilM33pl3/hexcom.git
        GIT_TAG         master
)
FetchContent_MakeAvailable(hex_client_lib)

add_subdirectory(hexmap)
add_subdirectory(apps)
