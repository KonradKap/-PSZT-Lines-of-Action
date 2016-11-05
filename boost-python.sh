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

dlibs=$(find /usr/lib/ -name "libboost_python*\.so")
slibs=$(find /usr/lib/ -name "libboost_python*\.a")
dlibs=(${dlibs// / })
slibs=(${slibs// / })

print_flags "${slibs[*]}" "boost_python3" && exit 0
print_flags "${dlibs[*]}" "boost_python3" "-Wl,Bdynamic" && exit 0

pyv=`python3 --version`
pyv=${pyv:7:-2}
pyv=${pyv/"."/""}

print_flags "${slibs[*]}" "boost_python-py$pyv" && exit 0
print_flags "${dlibs[*]}" "boost_python-py$pyv" "-Wl,Bdynamic" && exit 0
