#pragma once

#include <format>
#include <source_location>
#include <stdexcept>
#include <string>
#include <utility>


namespace stest {

    // Indicates a test case failure. Probably don't catch this anywhere in your own code.
    class TestAssertionFailure : public std::exception {
    public:
        TestAssertionFailure(std::string message) :
            _message{std::move(message)}
        {}

        char const* what() const override {
            return _message.c_str();
        }

    private:
        std::string _message;
    };


    namespace impl {
        // Throws a TestAssertionFailure with a nice message for the given source location.
        [[noreturn]]
        inline void throw_test_assertion_from(std::source_location location = std::source_location::current()) {
            throw TestAssertionFailure{std::format("\"{}\", line {}", location.file_name(), location.line())};
        }
    }


    // Asserts that expression is true. If expression is false, then TestAssertionFailure is thrown (and the test case
    // will exit and fail).
    inline void test_assert(bool expression, std::source_location location = std::source_location::current()) {
        if (!expression) {
            impl::throw_test_assertion_from(location);
        }
    }

    // Asserts that action throws an exception of type E (or derived). If no exception is thrown, then
    // TestAssertionFailure is thrown (and the test case will exit and fail).
    template<typename E>
    void test_assert_throws(auto&& action, std::source_location location = std::source_location::current()) {
        bool raised = false;
        try {
            action();
        }
        catch (E const& e) {
            raised = true;
        }
        if (!raised) {
            impl::throw_test_assertion_from(location);
        }
    }

    // Unconditionally throws TestAssertionFailure, immediately exiting and failing the test case.
    [[noreturn]]
    inline void fail_test(std::source_location location = std::source_location::current()) {
        impl::throw_test_assertion_from(location);
    }

}
