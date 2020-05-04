cmake_minimum_required(VERSION 3.16)
#set(CMAKE_USER_MAKE_RULES_OVERRIDE
#        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/c_flags_overrides.cmake)
#set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
#        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cxx_flags_overrides.cmake)

project(hexmap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
set(CMAKE_CXX_FLAGS "-I${CMAKE_CURRENT_LIST_DIR}/glad /EHsc")
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

LINK_DIRECTORIES(${CMAKE_BINARY_DIR})

add_library(hex_client_lib STATIC IMPORTED GLOBAL)
set_target_properties(hex_client_lib PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/hex_client_lib.lib)

add_library(libprotobufd STATIC IMPORTED GLOBAL)
set_target_properties(libprotobufd PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/libprotobufd.lib)

add_library(grpc++ STATIC IMPORTED GLOBAL)
set_target_properties(grpc++ PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/grpc++.lib)

add_library(grpc STATIC IMPORTED GLOBAL)
set_target_properties(grpc PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/grpc.lib)

add_library(gpr STATIC IMPORTED GLOBAL)
set_target_properties(gpr PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/gpr.lib)

add_library(grpc_plugin_support STATIC IMPORTED GLOBAL)
set_target_properties(grpc_plugin_support PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/grpc_plugin_support.lib)

add_library(address_sorting STATIC IMPORTED GLOBAL)
set_target_properties(address_sorting PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/address_sorting.lib)

add_library(ssl STATIC IMPORTED GLOBAL)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/ssl.lib)

add_library(crypto STATIC IMPORTED GLOBAL)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/crypto.lib)

add_library(upb STATIC IMPORTED GLOBAL)
set_target_properties(upb PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/upb.lib)

add_library(zlibstaticd STATIC IMPORTED GLOBAL)
set_target_properties(zlibstaticd PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/zlibstaticd.lib)

add_library(cares STATIC IMPORTED GLOBAL)
set_target_properties(cares PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bin/cares.lib)

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
ENDIF()

find_package(Boost REQUIRED COMPONENTS system atomic filesystem log exception)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(hexmap)
add_subdirectory(apps)
