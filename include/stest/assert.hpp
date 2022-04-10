#pragma once

#include <concepts>
#include <format>
#include <functional>
#include <source_location>
#include <stdexcept>
#include <string>
#include <utility>


namespace stest {

    // Indicates a test case failure. Probably don't catch this anywhere in your own code.
    class test_assertion_failure : public std::exception {
    public:
        test_assertion_failure(std::source_location location) :
            _location{std::move(location)},
            _message{std::format("\"{}\", line {}", location.file_name(), location.line())}
        {}

        [[nodiscard]]
        std::source_location const& where() const {
            return _location;
        }

        [[nodiscard]]
        char const* what() const override {
            return _message.c_str();
        }

    private:
        std::source_location _location;
        std::string _message;
    };


    // Asserts that expression is true. If expression is false, then test_assertion_failure is thrown (and the test case
    // will exit and fail).
    inline void test_assert(bool expression, std::source_location location = std::source_location::current()) {
        if (!expression) {
            throw test_assertion_failure{std::move(location)};
        }
    }

    // Asserts that action throws an exception of type E (or derived). If no exception is thrown, then
    // test_assertion_failure is thrown (and the test case will exit and fail).
    // If an exception is thrown, then this function will return it.
    template<std::movable E, std::invocable<> F>
    E test_assert_throws(F&& action, std::source_location location = std::source_location::current()) {
        try {
            (void)std::invoke(std::forward<F>(action));
        }
        catch (E& e) {
            return std::move(e);
        }
        throw test_assertion_failure{std::move(location)};
    }

    // Unconditionally throws test_assertion_failure, immediately exiting and failing the test case.
    [[noreturn]]
    inline void fail_test(std::source_location location = std::source_location::current()) {
        throw test_assertion_failure{std::move(location)};
    }

}
