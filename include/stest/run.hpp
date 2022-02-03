#pragma once

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "assert.hpp"
#include "test_case.hpp"


namespace stest {

    inline bool run_test_case(TestCase const& test_case) {
        std::cout << test_case.name;
        bool passed = false;
        try {
            test_case.function();
            passed = true;
        }
        catch (TestAssertionFailure const& e) {
            std::cout << ": FAILED - test assertion failed - " << e.what() << std::endl;
        }
        catch (std::exception const& e) {
            std::cout << ": FAILED - unhandled std::exception - " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << ": FAILED - unknown value thrown" << std::endl;
        }
        if (passed) {
            std::cout << ": passed" << std::endl;
        }
        return passed;
    }

    inline void run_test_cases(std::vector<TestCase> const& test_cases) {
        std::cout << "Running " << test_cases.size() << " tests...\n" << std::endl;
        std::vector<std::reference_wrapper<std::string const>> failed_cases;
        failed_cases.reserve(test_cases.size());
        for (auto const& test_case : test_cases) {
            auto const passed = run_test_case(test_case);
            if (!passed) {
                failed_cases.emplace_back(test_case.name);
            }
        }
        std::cout << "\nDone" << std::endl;
        auto const passed_count = test_cases.size() - failed_cases.size();
        std::cout << passed_count << " cases passed" << std::endl;
        std::cout << failed_cases.size() << " cases failed";
        if (failed_cases.empty()) {
            std::cout << std::endl;
        }
        else {
            std::cout << ':' << std::endl;
            for (auto const name : failed_cases) {
                std::cout << "  " << name.get() << std::endl;
            }
        }
    }

}