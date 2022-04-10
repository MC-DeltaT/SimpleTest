#pragma once

#include "test_case.hpp"


// Defines and registers a test case with the given name (a string).
// Usage:
//   STEST_CASE("my test case") = [] { ... };
// This macro can only be used in global or namespace scope.
#define STEST_CASE(name) \
    template<auto> extern int _stest_case_macro_helper; \
    template<> decltype(auto) _stest_case_macro_helper<([] {})> = ::stest::test_case(name)
