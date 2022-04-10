# SimpleTest: Simple unit testing for C++

by Reece Jones

## Overview

SimpleTest is designed to be an easy-to-use framework for basic unit testing tasks.  
Ever wanted to smash out a few quick unit tests, but don't want the extensive - but harder to use - features of, say, GoogleTest?
Then SimpleTest may be the framework for you!

## Features

 - Very simple to use
 - Basic boolean & exception assertions
 - Automatic `main()` generation
 - Concise test output & summary
 - No macros required

## Requirements

 - C++20
 - \[For CMake build\] CMake 3.22 or newer

## Usage

Include `stest/test_case.hpp` to define test cases, and `stest/assert.hpp` for assertions.  
Or just include `stest/stest.hpp` to get both.

Example `my_unit_tests.cpp`:

```c++
#include <stest/stest.hpp>

stest::test_block my_tests = [] {           // Introduces a block scope.
    stest::test_case("FooTest") = [] {      // Declares a test case.
        stest::test_assert(foo(3) == 9);    // Ensures an expression is true.
    };
};
```

`test_block` allows us to enter a block scope at namespace scope.

`test_case(name) = body` declares a test case, taking a `std::string` for the name and any callable for the test case body.

`test_assert(expression)` asserts that `expression` is `true`.

Other assertions available are:

 - `test_assert_throws<E>(callable)` - asserts `callable` throws `E`.
 - `fail_test()` - immediately fails the test.

### Macro-ful (not recommended)

As an alternative, if you really really want to use macros in exchange for even "simpler" code:

```c++
#include <stest/stest.hpp>
#include <stest/macros.hpp>

// No test_block required.
STEST_CASE("FooTest") = [] {
    stest::test_assert(foo(3) == 9);
};
```

## Importing

There are a few methods of importing SimpleTest, depending on your desired build process.

### CMake - `find_package()`

The recommended method is by installing and using `find_package()`, which will handle finding SimpleTest and checking version compatibility for you.

First, use CMake to install SimpleTest. Navigate to the SimpleTest repo directory, then:

```bash
mkdir build
cd build
cmake ..
# Admin/root privileges may be required for this step.
cmake --install .
```

This installs the SimpleTest source code and exported CMake targets to your system (e.g. on Windows: `C:/Program Files/SimpleTest`, on Linux: `/usr/local`).

(A custom install location can be specified with the `--prefix` install option, and then pointing CMake to that location via `SimpleTest_ROOT` or `CMAKE_PREFIX_PATH`.)

Then in your project's `CMakeLists.txt`:

```cmake
find_package(SimpleTest 1.0.0 REQUIRED)

add_executable(MyUnitTest my_unit_tests.cpp)
target_link_libraries(MyUnitTest PRIVATE SimpleTest::SimpleTest)
```

SimpleTest will inject a `main()` function into the `MyUnitTest` executable that will invoke all the test cases defined in `my_unit_tests.cpp`.  
If you don't want a `main()` injected, link to `SimpleTest::SimpleTestLib` instead.

### CMake - `add_subdirectory()`

```cmake
add_subdirectory(path/to/SimpleTest)
```

Targets will be available without the `SimpleTest::` namespace.

This is not recommended, especially for library projects, as there is no protection against duplicate imports or incompatible versions.

### Manual

Add `path/to/SimpleTest/include` to your include directories.

If you want a `main()` to be generated for you, compile and link `path/to/SimpleTest/src/stest/main.cpp`.

## Tests

Yes, even the testing framework has tests! (Otherwise how could you trust your test results?)  
The test code is contained in `test/` and the CMake target is `SimpleTestTest`.
The target will only be built if the CMake variable `SIMPLETEST_BUILD_TEST` is set to `ON`.
