cmake_minimum_required(VERSION 3.22)

project(SimpleTest CXX)

# Library without injected main().
add_library(SimpleTestLib src/run.cpp src/test_case.cpp)
target_include_directories(SimpleTestLib PUBLIC include/)
# We don't use C++23 features, but certain C++20 features are only implemented in some compilers' "latest" Standard
# mode, which currently corresponds to C++23.
target_compile_features(SimpleTestLib PUBLIC cxx_std_23)
set_target_properties(SimpleTestLib PROPERTIES CXX_EXTENSIONS OFF)

# Library with injected main().
add_library(SimpleTest src/main.cpp)
target_link_libraries(SimpleTest PUBLIC SimpleTestLib)
target_compile_features(SimpleTest PUBLIC cxx_std_23)
set_target_properties(SimpleTest PROPERTIES CXX_EXTENSIONS OFF)

add_executable(SimpleTestTest test/main.cpp)
target_link_libraries(SimpleTestTest PRIVATE SimpleTestLib)
target_compile_features(SimpleTestTest PUBLIC cxx_std_23)
set_target_properties(SimpleTestTest PROPERTIES CXX_EXTENSIONS OFF)
