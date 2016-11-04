#include <boost/python.hpp>

#include "app_example2.h"

BOOST_PYTHON_MODULE(lib_example2) {
    boost::python::def("hello_world", hello_world_);
}
