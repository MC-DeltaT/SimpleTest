#pragma once

#include <functional>
#include <string>
#include <vector>


namespace stest {

    struct TestCase {
        std::string name;
        std::function<void()> function;
    };


    std::vector<TestCase>& all_test_cases();

}


#define TEST_CASE(name) class TestCase_##name { \
    public: \
        static void test_func(); \
        static inline auto const register_helper = [] { \
            ::stest::all_test_cases().push_back({#name, test_func}); \
            return 0; \
        }(); \
    }; \
    void TestCase_##name::test_func()
