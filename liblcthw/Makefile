## THE BUILDER

# Common flags set for most of the projects
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)

# Flags set for linking a library
LIBS=-ldl $(OPTLIBS)

# DESTDIR and PREFIX defines where this library will be installed.
DESTDIR=/Users/shayangzang/Downloads/temp_c
PREFIX=/usr/local

# Define SOURCES var
SOURCES=$(wildcard src/**/*.c src/*.c)

# Define OBJECTS var as a list of *.o file names that are generated from a list of existing *.c files
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

TEST_SRC=$(wildcard tests/*_test.c)

# Define TESTS var as a list of executable names that are generated from a list of existing *.c files
# NOTE: object files *.o are usually not directly executable and this is a Makefile for a library project.
TESTS=$(patsubst %.c, %, $(TEST_SRC))

# TARGET build, name of our build
TARGET=build/mylib.a

# *.a files are statically linked library achives. When it is used in some project, the library code will be built into the project.
# *.so files are dynamically linked library achives, only involved and invoked during RUNTIME.
SO_TARGET=$(patsubst %.a, %.so, $(TARGET))

# This is the first target, aka default target run by command 'make'
# Build the above two targets and unit tests
# $(TARGET) $(SO_TARGET) tests, these three are pseudo-targets, defined as follows
all: $(TARGET) $(SO_TARGET) tests

# Make 'developer build'
dev: CFLAGS=-g -Wall -Isrc -Wextra $(OPTFLAGS)

dev: all

# Build target with additional flags
$(TARGET): CFLAGS += -fPIC

# Do the real work - build (static) library. Suited for small to median projects.
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

# Build dynamic library. Suited when multiple modules reference the lib.
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

# Make directories if they don't exist.
build:
	@mkdir -p build
	@mkdir -p bin

## THE UNIT TESTS

# Tag those that are not a real target with .PHONY so that make will ignore them
.PHONY: tests

# Build everything included in "TESTS" var with the current CFLAGS settings
tests: CFLAGS += $(TARGET)

# Run the shell script
tests: $(TESTS)
	sh ./runtests.sh

## THE CLEANER

# Clean up build directory, objects and tests, tests.log, *.gc* files and *.dSYM directories
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

## THE INSTALLER

# install: target depends on all target
install: all
	intstall -d $(DESTDIR)/$(PREFIX)/lib/
	intstall $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

## THE CHECKER

# run a check through src code for any usage of bad functions such as strcpy.
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
	   |stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
