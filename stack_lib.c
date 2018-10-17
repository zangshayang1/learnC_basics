#include <stdio.h>
#include "stack_lib.h"
#include "dbg.h"

// How to generate object code from src?
// > cc -Wall -g -DNDEBUG -c -o stack_lib.o stack_lib.c

// How to link it with main src to generate executable?
// > cc -Wall -g -DNDEBUG stack_main.c stack_lib.o -o stack_main


int THE_SIZE = 1000;

static int THE_AGE = 37; // static int cannot be accessed from outside of the file without accessors

int get_age() {
  return THE_AGE;
}

void set_age(int age) {
  THE_AGE = age;
}

double update_ratio(double new_ratio) {
  static double ratio = 1.0; // static var inside function can only be accessed within the function
  double old_ratio = ratio;
  ratio = new_ratio;
  return old_ratio;
}

void print_size() {
  log_info("Access THE_SIZE from inside of stack_lib.c => Size is: %d", THE_SIZE);
}
