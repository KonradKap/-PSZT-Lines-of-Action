#!/bin/bash
#
#Resolve different linking conventions for boost::python

function print_flags() {
    if [[ " $1 " =~ "$2" ]]
    then
        echo "$3 -l$2"
        return 0
    fi
    return 1
}

libs=$(find /usr/lib/ /usr/lib64/ -name "libboost_python*\.a" -o -name "libboost_python*\.so" 2>/dev/null)
libs=(${libs// / })

print_flags "${libs[*]}" "boost_python3" && exit 0

pyv=`python3 --version`
pyv=${pyv:7:-2}
pyv=${pyv/"."/""}

print_flags "${libs[*]}" "boost_python-py$pyv" && exit 0
