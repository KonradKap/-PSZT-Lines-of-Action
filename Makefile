# -Wall == all warnings enabled
#  # -Werror == treat warnings as ERRORS!
CXX = c++
CUR_DIR = $(shell pwd)
CPPFLAGS = --std=c++1y -Wall -Wextra -O3
INCLUDES = $(shell python3-config --includes) -I"$(CUR_DIR)/app" -I"$(CUR_DIR)/lib" -I"$(CUR_DIR)/tests"
LINKFLAGS = --std=c++1y -lstdc++ -lpthread -lm
SHAREDLFLAGS = $(shell bash boost-python.sh)
TESTLFLAGS = 

NODEPS=clean cleaner

app_SOURCES=$(shell find app/ -name *.cpp)
app_OBJECTS=$(app_SOURCES:app/%.cpp=bin/app/%.o)
app_SHARED =$(app_SOURCES:app/%.cpp=bin/lib/%.o)

lib_SOURCES=$(shell find lib/ -name *.cpp)
lib_OBJECTS=$(lib_SOURCES:lib/%.cpp=bin/lib/%.o)
lib_SHARED =$(lib_SOURCES:lib/%.cpp=bin/lib/%.so)

tests_SOURCES=$(shell find tests/ -name *.cpp)
tests_OBJECTS=$(tests_SOURCES:tests/%.cpp=bin/tests/%.o)
tests_EXECUTABLE = bin/tests_bin

DEPS=$(app_SOURCES:%.cpp=%.d) $(lib_SOURCES:%.cpp=%.d) $(tests_SOURCES:%.cpp=%.d)

all: shared tests

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif

bin/%.o : %.cpp %.d
	@mkdir -p $(@D)
	$(CXX) -c $(CPPFLAGS) $< -o $@ $(INCLUDES)

bin/lib/%.o : lib/%.cpp lib/%.d
	@mkdir -p $(@D)
	$(CXX) -c -fPIC $(CPPFLAGS) $< -o $@ $(INCLUDES)

bin/lib/%.o : app/%.cpp app/%.d
	@mkdir -p $(@D)
	$(CXX) -c -fPIC $(CPPFLAGS) $< -o $@ $(INCLUDES)

%.d : %.cpp
	$(CXX) $(CPPFLAGS) -MM -MT '$(patsubst %.cpp,bin/%.o,$<)' $< -MF $@ $(INCLUDES)

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
	@find . -name "*.d" -delete

cleaner: clean
	@rm -rf bin

.PHONY: clean cleaner tests shared
.SECONDARY: $(lib_OBJECTS) $(app_SHARED) $(DEPS)
