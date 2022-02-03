#pragma once

#include <vector>

#include "test_case.hpp"


namespace stest {

    // Runs a single test case, printing results to stdout.
    // Return value indicates if the test case was successful.
    bool run_test_case(TestCase const& test_case);

    // Runs multiple test cases in succession, printing results to stdout.
    void run_test_cases(std::vector<TestCase> const& test_cases);

}
