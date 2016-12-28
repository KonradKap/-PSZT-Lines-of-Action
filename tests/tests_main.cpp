#ifdef __MINGW32__
extern int putenv(char*);
#endif

#define BOOST_TEST_MODULE EXAMPLE
#include <boost/test/included/unit_test.hpp>
