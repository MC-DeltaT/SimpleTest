#include <algorithm>

#include <stest/run.hpp>
#include <stest/test_case.hpp>


int main() {
    auto& test_cases = stest::all_test_cases();
    std::ranges::sort(test_cases, [](auto const& a, auto const& b) {
        return a.name < b.name;
    });

    stest::run_test_cases(test_cases);
}
