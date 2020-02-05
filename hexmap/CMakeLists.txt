
add_library(hexmap_library STATIC HexagonMap.cpp)
target_compile_features(hexmap_library PRIVATE cxx_std_20)

target_include_directories(hexmap_library PUBLIC ../include)