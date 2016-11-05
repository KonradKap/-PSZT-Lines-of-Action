# -Wall == all warnings enabled
#  # -Werror == treat warnings as ERRORS!
CXX = c++
CUR_DIR = "$(shell pwd)"
CPPFLAGS = --std=c++1y -Wall -O0
INCLUDES = $(shell python3-config --includes) -I$(CUR_DIR)/app -I$(CUR_DIR)/lib -I$(CUR_DIR)/tests
LINKFLAGS = --std=c++1y -lstdc++
SHAREDLFLAGS = $(shell bash boost-python.sh)
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
	$(CXX) -c $(CPPFLAGS) $< -o $@ $(INCLUDES)

bin/lib/%.o : lib/%.cpp
	$(CXX) -c -fPIC $(CPPFLAGS) $< -o $@ $(INCLUDES)

bin/lib/%.o : app/%.cpp
	$(CXX) -c -fPIC $(CPPFLAGS) $< -o $@ $(INCLUDES)

bin/lib/%.so : bin/lib/%.o $(app_SHARED)
	$(CXX) -shared $< $(app_SHARED) -o $@ $(LINKFLAGS) $(SHAREDLFLAGS) $(INCLUDES)

bin/tests/%.o : tests/%.cpp
	$(CXX) -c $(CPPFLAGS) $< -o $@ $(INCLUDES)

$(tests_EXECUTABLE): $(tests_OBJECTS) $(app_OBJECTS)
	$(CXX) -o $@ $(tests_OBJECTS) $(app_OBJECTS) $(LINKFLAGS) $(TESTLFLAGS) $(INCLUDES)

tests: $(tests_EXECUTABLE)
	./$(tests_EXECUTABLE)

.PHONY: clean tests
.SECONDARY: $(lib_OBJECTS) $(app_SHARED)

clean:
	- rm bin/lib/*.so  || true
	- rm bin/lib/*.o   || true
	- rm bin/app/*.o   || true
	- rm bin/tests/*.o || true
	- rm bin/tests_bin || true
