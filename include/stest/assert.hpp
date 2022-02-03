#pragma once

#include <format>
#include <source_location>
#include <stdexcept>
#include <string>
#include <utility>


namespace stest {

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
        [[noreturn]]
        inline void throw_test_assertion_from(std::source_location location = std::source_location::current()) {
            throw TestAssertionFailure{std::format("\"{}\", line {}", location.file_name(), location.line())};
        }
    }


    inline void test_assert(bool expression, std::source_location location = std::source_location::current()) {
        if (!expression) {
            impl::throw_test_assertion_from(location);
        }
    }

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

    [[noreturn]]
    inline void fail_test(std::source_location location = std::source_location::current()) {
        impl::throw_test_assertion_from(location);
    }

}
