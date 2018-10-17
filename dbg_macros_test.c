#include "./dbg.h"
#include <stdlib.h>
#include <stdio.h>

void test_debug() {
  debug("This is a line of debug info.");
  debug("More debug info with arbitrary arguments: %s, %d.", "hehe", 1);
}

void test_log_err() {
  log_err("This is some error log.");
  log_err("More error log with arbitrary arguments: %s, %d", "hehe", 1);
}

void test_log_warn() {
  log_warn("This is some warning log.");
  log_warn("More warning log with arbitrary arguments: %s, %d", "hehe", 1);
}

void test_log_info() {
  log_info("This is some info log.");
  log_info("More info log with arbitrary arguments: %s, %d", "hehe", 1);
}

int test_check(char *filename) {
  char* block = NULL;
  block = malloc(100);
  check_mem(block); // print OOM if malloc failed.
  if (block) free(block);


  FILE* input = fopen(filename, "r"); // fail when the file doesn't exist.
  check(input, "Failed to open %s.", filename);
  if (input) fclose(input);
  return 0;

error:
  if (block) free(block);
  if (input) fclose(input);
  return -1;
}

int test_sentinel(int code) {
  char* block = malloc(100);
  check_mem(block);
  switch (code) {
    case 1:
      log_info("It worked.");
      break;
    default:
      sentinel("Sentinel speaks.");
  }

  if (block) free(block);
  return 0;

error:
  if (block) free(block);
  return -1;
}

int test_check_mem() {
  char* test = NULL;
  check_mem(test);
  return 1;

error:
  return -1;
}

int test_check_debug() {
  int i = 0;
  check_debug(i != 0, "Oops, I was 0.");
  return 0;

error:
  return -1;
}

int main(int argc, char* argv[]) {
  check(argc == 2, "Need an argument.");

  test_debug();
  test_log_err();
  test_log_warn();
  test_log_info();

  test_check("dbg_macros_test.c");
  check(test_check(argv[1]) == -1, "Failed to open argv-specific file");

  test_sentinel(1);
  check(test_sentinel(100) == -1, "test_sentinel failed because I made it so.");

  test_check_mem();

  test_check_debug();

  return 0;

error:
  return 1;
}
