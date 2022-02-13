#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <source_location>
#include <sstream>
#include <stdexcept>

#include <stest/assert.hpp>
#include <stest/run.hpp>
#include <stest/test_case.hpp>


static std::size_t failures = 0;

bool fail(std::source_location location = std::source_location::current()) {
    ++failures;
    std::cout << "Failure on line " << location.line() << std::endl;
    return false;
}


static bool test_case_pass_run = false;
STEST_CASE(TestCase_Pass) {
    test_case_pass_run = true;
}

static bool test_case_fail_assertion_run = false;
STEST_CASE(TestCase_FailAssertion) {
    test_case_fail_assertion_run = true;
    stest::test_assert(false);
}

static bool test_case_fail_stdexception_run = false;
STEST_CASE(TestCase_FailStdException) {
    test_case_fail_stdexception_run = true;
    throw std::invalid_argument{"Whoops"};
}

static bool test_case_fail_throw_run = false;
STEST_CASE(TestCase_FailThrow) {
    test_case_fail_throw_run = true;
    throw "hello world";
}


int main() {
    /* assert.hpp */

    try {
        stest::fail_test();
        fail();
    }
    catch (stest::TestAssertionFailure const&) {}

    stest::test_assert(42 == 13 + 29);

    try {
        stest::test_assert(1 + 1 == 3);
    }
    catch (stest::TestAssertionFailure const&) {}

    {
        auto const e = stest::test_assert_throws<std::logic_error>([] { throw std::logic_error{"code broken"}; });
        std::strcmp(e.what(), "code broken") == 0 || fail();
    }

    {
        auto const e = stest::test_assert_throws<std::exception>([] { throw std::runtime_error{"Oh no!"}; });
        std::strcmp(e.what(), "Oh no!") == 0 || fail();
    }

    try {
        stest::test_assert_throws<std::invalid_argument>([] {});
        fail();
    }
    catch (stest::TestAssertionFailure const&) {}


    /* test_case.hpp, test_case.cpp */

    stest::all_test_cases().size() == 4 || fail();

    {
        auto const& test_case = stest::all_test_cases().at(0);
        test_case.name == "TestCase_Pass" || fail();
        !test_case_pass_run || fail();
        test_case.function();
        test_case_pass_run || fail();
        test_case_pass_run = false;
    }


    /* run.hpp, run.cpp */

    {
        std::stringstream stream;
        auto const success = stest::run_test_cases(stest::all_test_cases(), stream);
        
        !success || fail();

        auto const text = stream.str();

        text.starts_with("Running 4 test cases...\n") || fail();

        test_case_pass_run || fail();
        text.contains("TestCase_Pass: passed") || fail();

        test_case_fail_assertion_run || fail();
        text.contains("TestCase_FailAssertion: FAILED - test assertion failed") || fail();

        test_case_fail_stdexception_run || fail();
        text.contains("TestCase_FailStdException: FAILED - unhandled std::exception") || fail();

        test_case_fail_throw_run || fail();
        text.contains("TestCase_FailThrow: FAILED - unhandled thrown value") || fail();

        std::string const expected_end =
            "\nDone\n"
            "1 cases passed\n"
            "3 cases failed:\n"
            "  TestCase_FailAssertion\n"
            "  TestCase_FailStdException\n"
            "  TestCase_FailThrow\n";
        text.ends_with(expected_end) || fail();
    }


    std::cout << "Done, with " << failures << " failures" << std::endl;

    if (failures) {
        return EXIT_FAILURE;
    }
    else {
        return EXIT_SUCCESS;
    }
}
