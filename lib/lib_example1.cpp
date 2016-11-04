#include <iostream>

#include <boost/python.hpp>

#include "app_example1.h"

BOOST_PYTHON_MODULE(lib_example1) {
    boost::python::def("hello_world", hello_world);
}
