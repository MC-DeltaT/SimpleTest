#pragma once

#include <iostream>
#include <ostream>
#include <vector>

#include "test_case.hpp"


namespace stest {

    // Runs a single test case, printing results to stream.
    // Return value indicates if the test case was successful.
    bool run_test_case(TestCase const& test_case, std::ostream& stream = std::cout);

    // Runs multiple test cases in succession, printing results to stream.
    // Return value indicates if all test cases were successful.
    bool run_test_cases(std::vector<TestCase> const& test_cases, std::ostream& stream = std::cout);

}
