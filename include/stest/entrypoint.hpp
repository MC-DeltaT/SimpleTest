#pragma once

#include <algorithm>
#include <cstdlib>

#include "run.hpp"
#include "test_case.hpp"


namespace stest {

    // Basic application entrypoint that runs all test cases.
    inline int entrypoint(int, char**) {
        auto& test_cases = stest::all_test_cases();
        std::ranges::sort(test_cases, [](auto const& a, auto const& b) {
            return a.name < b.name;
        });

        auto const success = stest::run_test_cases(test_cases);

        if (success) {
            return EXIT_SUCCESS;
        }
        else {
            return EXIT_FAILURE;
        }
    }

}

