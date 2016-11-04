#include <boost/test/included/unit_test.hpp>

#include "app_example2.h"

BOOST_AUTO_TEST_SUITE(JumperTests)

BOOST_AUTO_TEST_CASE(SanityCheck) {
    BOOST_CHECK_EQUAL(1, 1);
}

BOOST_AUTO_TEST_CASE(AppMethodCall) {
    BOOST_CHECK_EQUAL(hello_world_(), "Hello world");
}

BOOST_AUTO_TEST_SUITE_END()
