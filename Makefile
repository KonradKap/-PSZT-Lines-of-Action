# -Wall == all warnings enabled
#  # -Werror == treat warnings as ERRORS!
CXX = c++
CUR_DIR = "$(shell pwd)"
CPPFLAGS = --std=c++1y -Wall -O0
INCLUDES = $(shell python3-config --includes) -I$(CUR_DIR)/app -I$(CUR_DIR)/lib -I$(CUR_DIR)/tests
LINKFLAGS = --std=c++1y -lstdc++
SHAREDLFLAGS = $(shell bash boost-python.sh)
TESTLFLAGS = -lboost_unit_test_framework

app_SOURCES=$(shell find app/ -name *.cpp)
app_OBJECTS=$(app_SOURCES:app/%.cpp=bin/app/%.o)
app_SHARED =$(app_SOURCES:app/%.cpp=bin/lib/%.o)

lib_SOURCES=$(shell find lib/ -name *.cpp)
lib_OBJECTS=$(lib_SOURCES:lib/%.cpp=bin/lib/%.o)
lib_SHARED =$(lib_SOURCES:lib/%.cpp=bin/lib/%.so)

tests_SOURCES=$(shell find tests/ -name *.cpp)
tests_OBJECTS=$(tests_SOURCES:tests/%.cpp=bin/tests/%.o)
tests_EXECUTABLE = bin/tests_bin

all: shared tests

bin/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CPPFLAGS) $< -o $@ $(INCLUDES)

bin/lib/%.o : */%.cpp
	@mkdir -p $(@D)
	$(CXX) -c -fPIC $(CPPFLAGS) $< -o $@ $(INCLUDES)

%.so : %.o $(app_SHARED)
	@mkdir -p $(@D)
	$(CXX) -shared $< $(app_SHARED) -o $@ $(LINKFLAGS) $(SHAREDLFLAGS) $(INCLUDES)

$(tests_EXECUTABLE): $(tests_OBJECTS) $(app_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) -o $@ $(tests_OBJECTS) $(app_OBJECTS) $(LINKFLAGS) $(TESTLFLAGS) $(INCLUDES)

tests: $(tests_EXECUTABLE)
	@./$(tests_EXECUTABLE)

shared: $(lib_SHARED)
	@for dir in $$(ls -d bin/lib/*/);\
		do find $$dir -name '*.so' -print0 | xargs -0r mv -ut bin/lib/;\
	done

clean:
	@find . -name "*.o" -delete
	@find . -type d -empty -delete

cleaner:
	@rm -rf bin

.PHONY: clean cleaner tests shared
.SECONDARY: $(lib_OBJECTS) $(app_SHARED)
