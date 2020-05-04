
#set(glfw3_DIR /Users/olivier.vanacker/homebrew/Cellar/glfw/3.3/lib/cmake/glfw3/)
add_executable(hexmapcli hexmapcli.cpp)

target_link_libraries(hexmapcli hexmap_library Boost::exception glfw cli hex_client_lib libprotobufd grpc++ grpc gpr ssl crypto upb zlibstaticd address_sorting cares Boost::atomic Boost::thread Boost::system)

target_include_directories(hexmapcli PUBLIC ${OPENGL_INCLUDE_DIR})
#target_link_libraries(hexmapcli ${OPENGsL_gl_LIBRARY} hex_library)
if (APPLE)
    target_link_libraries(hexmapcli "-framework OpenGL")
endif()