#include "stack_lib.h"
#include "dbg.h"

// Refer to stack_lib.c for compile instructions

const char* MY_NAME = "Sean Zang";

void scope_demo(int count) {
  log_info("count is: %d.", count);
  if (count > 10) {
    log_info("count inside 'if > 10' condition scope is: %d.", count);
  }
  log_info("count is at exit: %d", count);
  count = 3000;
  log_info("count after assign: %d.", count);
}

int main(int argc, char* argv[]) {

  // test accessors to THE_AGE
  log_info("My name: %s, age: %d.", MY_NAME, get_age());
  set_age(100);
  log_info("My age is now: %d.", get_age());

  // test extern to THE_SIZE
  log_info("THE_SIZE is: %d.", THE_SIZE);
  print_size();

  // test ratio function static
  log_info("Ratio at first: %f.", update_ratio(2.0));
  log_info("Ratio at again: %f.", update_ratio(10.0));
  log_info("Ratio at once more: %f.", update_ratio(300.0));

  // test scope_demo
  int count = 4;
  scope_demo(count);
  scope_demo(count * 20);

  log_info("count after calling scope_demo: %d.", count);

  return 0;
}
