#include <boost/test/auto_unit_test.hpp>

#include "print_log_value.h"

#include "MinMaxRunner.h"

BOOST_AUTO_TEST_SUITE(RunnerTests)

BOOST_AUTO_TEST_CASE(Check) {
    MinMaxRunner runner;
    const auto result = runner.run_for(std::chrono::milliseconds(1), Board());
    BOOST_CHECK_EQUAL(result, std::vector<int>({2, 3, 4, 5}));
}

BOOST_AUTO_TEST_SUITE_END()
