add_executable(dfly main.cpp)
target_link_libraries(dfly PRIVATE dragonfly_core)
target_compile_features(dfly PRIVATE cxx_std_20)