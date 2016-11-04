# -Wall == all warnings enabled
#  # -Werror == treat warnings as ERRORS!
CXX = c++
CUR_DIR = $(shell pwd)
CPPFLAGS = --std=c++1y -Wall -Werror -O0 -I/usr/include/python3.4 -I$(CUR_DIR)/app -I$(CUR_DIR)/lib -I$(CUR_DIR)/tests
LINKFLAGS = --std=c++1y -lstdc++
SHAREDLFLAGS = -lboost_python-py34
TESTLFLAGS = -lboost_unit_test_framework

app_SOURCES=$(wildcard app/*.cpp)
app_OBJECTS=$(app_SOURCES:app/%.cpp=bin/app/%.o)
app_SHARED =$(app_SOURCES:app/%.cpp=bin/lib/%.o)

lib_SOURCES=$(wildcard lib/*.cpp)
lib_OBJECTS=$(lib_SOURCES:lib/%.cpp=bin/lib/%.o)
lib_SHARED =$(lib_SOURCES:lib/%.cpp=bin/lib/%.so)

tests_SOURCES = $(wildcard tests/*.cpp)
tests_OBJECTS=$(tests_SOURCES:tests/%.cpp=bin/tests/%.o)
tests_EXECUTABLE = bin/tests_bin

all: directories $(lib_SHARED) tests

directories:
	@mkdir -p bin/app
	@mkdir -p bin/lib
	@mkdir -p bin/tests

bin/app/%.o : app/%.cpp
	$(CXX) -c $(CPPFLAGS) $< -o $@

bin/lib/%.o : lib/%.cpp
	$(CXX) -c -fPIC $(CPPFLAGS) $< -o $@

bin/lib/%.o : app/%.cpp
	$(CXX) -c -fPIC $(CPPFLAGS) $< -o $@

bin/lib/%.so : bin/lib/%.o $(app_SHARED)
	$(CXX) -shared $< $(app_SHARED) -o $@ $(LINKFLAGS) $(SHAREDLFLAGS)

bin/tests/%.o : tests/%.cpp
	$(CXX) -c $(CPPFLAGS) $< -o $@

$(tests_EXECUTABLE): $(tests_OBJECTS) $(app_OBJECTS)
	$(CXX) -o $@ $(tests_OBJECTS) $(app_OBJECTS) $(LINKFLAGS) $(TESTLFLAGS)

tests: $(tests_EXECUTABLE)
	./$(tests_EXECUTABLE)

.PHONY: clean tests
.SECONDARY: $(lib_OBJECTS)

clean:
	- rm bin/lib/*.so  || true
	- rm bin/lib/*.o   || true
	- rm bin/app/*.o   || true
	- rm bin/tests/*.o || true
	- rm bin/tests_bin || true
