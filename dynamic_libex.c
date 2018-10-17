#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

/*
  compile lib src code to object code
  > cc -c dynamic_lib.c -o dynamic_lib.o

  make dynamic lib archive
  > cc -shared -o dynamic_lib.so dynamic_lib.o

  make this executable
  > cc -Wall -g -DNDEBUG dynamic_libex.c -ldl -o dynamic_libex
*/

// define a function pointer type with respect to the function you want to use from dynamic_lib.c
typedef int (*lib_function) (const char* data);

int main(int argc, char *argv[]) {
  int rc = 0;
  check(argc == 4, "USAGE: dynamic_libex dynamic_lib.so function data");

  char* lib_filename = argv[1]; // dynamic_lib.so - built from dynamic_lib.c
  char* func_name = argv[2]; // provide the name of the function you want to run from dynamic_lib.c
  char* data = argv[3]; // data that will be passed into the function

  // RTLD_NOW, opposed to RTLD_LAZY, means resolve undefined symbols before dlopen returns
  void* lib = dlopen(lib_filename, RTLD_NOW); // returns a handle on lib
  check(lib != NULL, "Failed to open the lib: %s: %s", lib_filename, dlerror());

  lib_function func = dlsym(lib, func_name); // power point
  check(func != NULL, "Did not find %s function in the lib %s: %s", func_name, lib_filename, dlerror());

  rc = func(data);
  check(rc == 0, "Function %s return %d for data: %s", func_name, rc, data);

  rc = dlclose(lib);
  check(rc == 0, "Failed to close %s", lib_filename);

  return 0;

error:
  return 1;
}
