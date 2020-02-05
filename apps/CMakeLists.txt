
#set(glfw3_DIR /Users/olivier.vanacker/homebrew/Cellar/glfw/3.3/lib/cmake/glfw3/)
set(CMAKE_CXX_FLAGS "-I${CMAKE_CURRENT_LIST_DIR}/glad")

#find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(hexmapcli hexmapcli.cpp glad/glad.c)

target_link_libraries(hexmapcli glfw hexmap_library)

target_include_directories(hexmapcli PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(hexmapcli ${OPENGsL_gl_LIBRARY} hex_library)
if (APPLE)
    target_link_libraries(hexmapcli "-framework OpenGL")
endif()