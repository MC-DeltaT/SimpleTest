cmake_minimum_required(VERSION 3.22)

project(SimpleTest VERSION 1.0.0 LANGUAGES CXX)
# TODO: update version when making changes.

# Library without injected main().
add_library(SimpleTestLib INTERFACE)
target_include_directories(SimpleTestLib INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    $<INSTALL_INTERFACE:include>)
# We don't use C++23 features, but certain C++20 features are only implemented in some compilers' "latest" Standard
# mode, which currently corresponds to C++23.
target_compile_features(SimpleTestLib INTERFACE cxx_std_23)
set_target_properties(SimpleTestLib PROPERTIES CXX_EXTENSIONS OFF)

# Library with injected main().
add_library(SimpleTest INTERFACE)
target_sources(SimpleTest INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/stest/main.cpp>"
    $<INSTALL_INTERFACE:src/stest/main.cpp>)
target_link_libraries(SimpleTest INTERFACE SimpleTestLib)
target_compile_features(SimpleTest INTERFACE cxx_std_23)
set_target_properties(SimpleTest PROPERTIES CXX_EXTENSIONS OFF)

# Only build test code if specifically requested.
option(SIMPLETEST_BUILD_TEST "Build test executable" OFF)
if(SIMPLETEST_BUILD_TEST)
    message("Configuring to build SimpleTestTest")
    add_executable(SimpleTestTest test/main.cpp test/tests.cpp)
    target_link_libraries(SimpleTestTest PRIVATE SimpleTestLib)
    target_compile_features(SimpleTestTest PUBLIC cxx_std_23)
    set_target_properties(SimpleTestTest PROPERTIES CXX_EXTENSIONS OFF)
endif()

# Don't configure installation if we're part of another project.
if(PROJECT_IS_TOP_LEVEL)
    # Set up targets for installation.
    include(GNUInstallDirs)
    install(TARGETS SimpleTestLib SimpleTest EXPORT "${PROJECT_NAME}Targets")
    install(EXPORT "${PROJECT_NAME}Targets" NAMESPACE "${PROJECT_NAME}::" DESTINATION cmake)
    # Copy source files.
    install(DIRECTORY include/ DESTINATION include)
    install(DIRECTORY src/ DESTINATION src)

    # Set up Config.cmake and ConfigVersion.cmake files for usage with find_package().
    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION cmake)
    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" COMPATIBILITY SameMajorVersion)
    install(FILES
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION cmake)
endif()
