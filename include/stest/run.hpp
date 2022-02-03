#pragma once

#include <vector>

#include "test_case.hpp"


namespace stest {

    bool run_test_case(TestCase const& test_case);

    void run_test_cases(std::vector<TestCase> const& test_cases);

}
