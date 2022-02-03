cmake_minimum_required(VERSION 3.22)

project(SimpleTest CXX)

add_library(SimpleTest src/main.cpp src/run.cpp src/test_case.cpp)
target_include_directories(SimpleTest PUBLIC include/)
target_compile_features(SimpleTest PUBLIC cxx_std_23)
set_target_properties(SimpleTest PROPERTIES CXX_EXTENSIONS OFF)
