#pragma once

#include <concepts>
#include <functional>
#include <string>
#include <utility>
#include <vector>


namespace stest {

    // Used to introduce a block scope which is executed immediately.
    // Helpful for using test_case() at global or namespace scope.
    struct test_block {
        template<std::invocable<> F>
        test_block(F&& body) {
            std::invoke(std::forward<F>(body));
        }
    };


    // Data for a single test.
    struct test_case_t {
        std::string name;
        std::function<void()> function;
    };


    // Contains all test cases for the current program.
    // It's safe to modify this at just about any time (but no thread synchronisation is provided).
    inline std::vector<test_case_t>& all_test_cases() {
        static std::vector<test_case_t> test_cases;
        return test_cases;
    }


    namespace detail {

        struct test_case_proxy {
            std::string name;

            explicit test_case_proxy(std::string name) :
                name{std::move(name)}
            {}

            template<std::invocable<> F>
            test_case_t& operator=(F&& function) && {
                return all_test_cases().emplace_back(std::move(name), std::forward<F>(function));
            }
        };

    }


    // Used to define and register a test case with the given name.
    // Usage:
    //   test_case("my test case") = [] { ... };
    // To use at global or namespace scope, use within a test_block.
    inline detail::test_case_proxy test_case(std::string name) {
        return detail::test_case_proxy{std::move(name)};
    }

}
