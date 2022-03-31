#pragma once

#include <functional>
#include <string>
#include <vector>


namespace stest {

    // A single test.
    struct TestCase {
        std::string name;       // Unique identifier for the test.
        std::function<void()> function;
    };


    // Contains all test cases for the current program.
    // It's safe to modify this at just about any time (but no thread synchronisation is provided).
    inline std::vector<TestCase>& all_test_cases() {
        static std::vector<TestCase> test_cases;
        return test_cases;
    }

}


// Defines and registers a test case with the given name.
// This should only be used in global or namespace scope.
// Test cases are uniquely identified by name, so make sure to only define each one once! (I.e. probably don't define
// test cases in headers.)
#define STEST_CASE(name) class STestCase_##name { \
    public: \
        static void test_func(); \
        static inline auto const register_helper = [] { \
            ::stest::all_test_cases().push_back({#name, test_func}); \
            return 0; \
        }(); \
    }; \
    void STestCase_##name::test_func()
