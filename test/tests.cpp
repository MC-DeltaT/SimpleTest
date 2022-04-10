#include <stest/stest.hpp>
#include <stest/macros.hpp>


// Put these tests in a separate source file to make sure no weird linker stuff happens across translation units.

bool test_case_pass_run = false;
stest::test_block test_case_pass_block = [] {
    stest::test_case("TestCase_Pass") = [] {
        test_case_pass_run = true;
    };
};

bool test_case_fail_assertion_run = false;
namespace test {
    stest::test_block test_case_fail_assertion_block = [] {
        stest::test_case("TestCase_FailAssertion") = [] {
            test_case_fail_assertion_run = true;
            stest::test_assert(false);
        };
    };
}

bool test_case_fail_stdexception_run = false;
STEST_CASE("TestCase_FailStdException") = [] {
    test_case_fail_stdexception_run = true;
    throw std::invalid_argument{"Whoops"};
};

bool test_case_fail_throw_run = false;
namespace test {
    STEST_CASE("TestCase_FailThrow") = [] {
        test_case_fail_throw_run = true;
        throw "hello world";
    };
}
