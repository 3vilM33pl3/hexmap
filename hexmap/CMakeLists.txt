#find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(hexmap_library STATIC HexagonMap.cpp glad/glad.c)
target_compile_features(hexmap_library PRIVATE cxx_std_20)


target_include_directories(hexmap_library PUBLIC ../include ${OPENGL_INCLUDE_DIR})



target_link_libraries(hexmap_library glfw ${OPENGsL_gl_LIBRARY} hex_client_lib)
if (APPLE)
    target_link_libraries(hexmap_library "-framework OpenGL")
endif()