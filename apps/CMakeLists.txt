
#set(glfw3_DIR /Users/olivier.vanacker/homebrew/Cellar/glfw/3.3/lib/cmake/glfw3/)
set(CMAKE_CXX_FLAGS "-I${CMAKE_CURRENT_LIST_DIR}/glad")

find_package(OpenGL REQUIRED)

FetchContent_Declare(
        cli
        GIT_REPOSITORY  https://github.com/daniele77/cli.git
        GIT_TAG         v1.1.1
)
FetchContent_MakeAvailable(cli)

add_executable(hexmapcli hexmapcli.cpp)

target_link_libraries(hexmapcli hexmap_library glfw cli)

target_include_directories(hexmapcli PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(hexmapcli ${OPENGsL_gl_LIBRARY} hex_library)
if (APPLE)
    target_link_libraries(hexmapcli "-framework OpenGL")
endif()