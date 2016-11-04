#!/usr/bin/python3

import sys
import os
sys.path.append(os.getcwd() + "/bin/lib")
import lib_example1
import lib_example2

lib_example1.hello_world()
print(lib_example2.hello_world())
