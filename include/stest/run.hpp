#pragma once

#include <functional>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "assert.hpp"
#include "test_case.hpp"


namespace stest {

    // Runs a single test case, printing results to stream.
    // Return value indicates if the test case was successful.
    inline bool run_test_case(test_case_t const& test_case, std::ostream& stream = std::cout) {
        stream << test_case.name << ": ";
        bool passed = false;
        try {
            test_case.function();
            passed = true;
        }
        catch (test_assertion_failure const& e) {
            stream << "FAILED - test assertion failed - " << e.what() << std::endl;
        }
        catch (std::exception const& e) {
            stream << "FAILED - unhandled std::exception - " << e.what() << std::endl;
        }
        catch (...) {
            stream << "FAILED - unhandled thrown value" << std::endl;
        }
        if (passed) {
            stream << "passed" << std::endl;
        }
        return passed;
    }

    // Runs multiple test cases in succession, printing results to stream.
    // Return value indicates if all test cases were successful.
    inline bool run_test_cases(std::vector<test_case_t> const& test_cases, std::ostream& stream = std::cout) {
        stream << "Running " << test_cases.size() << " test cases...\n" << std::endl;
        std::vector<std::reference_wrapper<std::string const>> failed_cases;
        failed_cases.reserve(test_cases.size());
        for (auto const& test_case : test_cases) {
            auto const passed = run_test_case(test_case, stream);
            if (!passed) {
                failed_cases.emplace_back(test_case.name);
            }
        }
        
        stream << "\nDone" << std::endl;
        auto const passed_count = test_cases.size() - failed_cases.size();
        stream << passed_count << " cases passed" << std::endl;
        stream << failed_cases.size() << " cases failed";
        if (failed_cases.empty()) {
            stream << std::endl;
        }
        else {
            stream << ':' << std::endl;
            for (auto const name : failed_cases) {
                stream << "  " << name.get() << std::endl;
            }
        }

        return failed_cases.empty();
    }

}
