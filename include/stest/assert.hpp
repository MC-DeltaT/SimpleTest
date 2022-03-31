#pragma once

#include <concepts>
#include <format>
#include <source_location>
#include <stdexcept>
#include <string>
#include <utility>


namespace stest {

    // Indicates a test case failure. Probably don't catch this anywhere in your own code.
    class TestAssertionFailure : public std::exception {
    public:
        TestAssertionFailure(std::source_location location) :
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


    // Asserts that expression is true. If expression is false, then TestAssertionFailure is thrown (and the test case
    // will exit and fail).
    inline void test_assert(bool expression, std::source_location location = std::source_location::current()) {
        if (!expression) {
            throw TestAssertionFailure{std::move(location)};
        }
    }

    // Asserts that action throws an exception of type E (or derived). If no exception is thrown, then
    // TestAssertionFailure is thrown (and the test case will exit and fail).
    // If an exception is thrown, then this function will return it.
    template<std::movable E>
    E test_assert_throws(std::invocable<> auto&& action,
            std::source_location location = std::source_location::current()) {
        try {
            (void)action();
        }
        catch (E& e) {
            return std::move(e);
        }
        throw TestAssertionFailure{std::move(location)};
    }

    // Unconditionally throws TestAssertionFailure, immediately exiting and failing the test case.
    [[noreturn]]
    inline void fail_test(std::source_location location = std::source_location::current()) {
        throw TestAssertionFailure{std::move(location)};
    }

}
