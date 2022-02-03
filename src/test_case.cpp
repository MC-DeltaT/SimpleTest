#include <stest/test_case.hpp>

#include <vector>


namespace stest {

    std::vector<TestCase>& all_test_cases() {
        static std::vector<TestCase> test_cases;
        return test_cases;
    }

}
