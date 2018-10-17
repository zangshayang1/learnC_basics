#include "minunit.h"
#include "../src/lcthw/list_sort.h"
#include "../src/lcthw/dbg.h"
#include "../src/lcthw/list.h"
#include <assert.h>
#include <string.h>

char* VALUES[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
// TODO: string declaration is not using heap memory and thus free always fails.

static List* words = NULL;

#define NUM_VALUES 5

List* create_words() {
  List* words = List_create();
  for(int i = 0; i < NUM_VALUES; i++) {
    List_push(words, VALUES[i]);
  }
  return words;
}

int is_sorted(List* words) {
  LIST_FOREACH(words, first, next, cur) {
    if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
      debug("%s %s", (char*)cur->value, (char*)cur->next->value);
      return 0;
    }
  }
  return 1; // true
}

char* test_bubble_sort() {
  int rc = -1;

  // should work on empty list
  List* empty_list = List_create();
  rc = List_bubble_sort(empty_list, (List_compare) strcmp);
  mu_assert(rc == 0, "List_bubble_sort failed on empty list.");

  // should work on test list
  words = create_words();
  rc = List_bubble_sort(words, (List_compare) strcmp);
  mu_assert(rc == 0, "List_bubble_sort failed on test list.");
  mu_assert(is_sorted(words), "Failed to bubble sort test list correctly.");

  List_clear_destroy(words);
  return NULL;
}

char* test_merge_sort() {
  // should work on test list
  words = create_words();
  List* rst = List_merge_sort(words, (List_compare) strcmp);
  mu_assert(is_sorted(rst), "Failed to merge sort test list correctly.");

  List_clear_destroy(words);
  return NULL;
}

char* all_tests() {
  mu_suite_start();
  mu_run_test(test_bubble_sort);
  mu_run_test(test_merge_sort);
  return NULL;
}

RUN_TESTS(all_tests);
