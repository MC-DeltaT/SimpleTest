cmake_minimum_required(VERSION 3.22)

project(SimpleTest CXX)

add_library(SimpleTest src/main.cpp src/run.cpp src/test_case.cpp)
target_include_directories(SimpleTest PUBLIC include/)
# We don't use C++23 features, but certain C++20 features are only implemented in some compilers' "latest" Standard
# mode, which currently corresponds to C++23.
target_compile_features(SimpleTest PUBLIC cxx_std_23)
set_target_properties(SimpleTest PROPERTIES CXX_EXTENSIONS OFF)
