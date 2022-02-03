# SimpleTest: A simple unit testing framework for C++

by Reece Jones

## Overview

SimpleTest is designed to be an easy-to-use framework for basic unit testing tasks.  
Ever wanted to smash out a few quick unit tests, but don't want the extensive (but harder to use) features of, say, GoogleTest? Then SimpleTest may be the framework for you!

## Requirements

 - CMake 3.22 or newer
 - C++20

## Usage

### CMake

Add the SimpleTest project root:

```cmake
add_subdirectory(path/to/SimpleTest)
```

Then add SimpleTest to your executable:

```cmake
add_executable(MyUnitTest unit_tests.cpp)
target_link_libraries(MyUnitTest SimpleTest)
```

SimpleTest will inject a `main()` function into the `MyUnitTest` executable that will invoke all the test cases defined in `unit_tests.cpp`.

### Code

Include `stest/test_case.hpp` to define test cases, and `stest/assert.hpp` for assertions.  
Or just include `stest/stest.hpp` to get both.

`STEST_CASE(name) { ... }` is used to define a test case.  
Assertions include:

 - `test_assert(expression)` - asserts `expression` is `true`.
 - `test_assert_throws<E>(function)` - asserts `function` throws `E`.
 - `fail_test()` - instantly fails the test.

Example `unit_tests.cpp`:
```c++
#include <stest/stest.hpp>

STEST_CASE(FooTest) {
    stest::test_assert(foo(3) == 9);
}
```
