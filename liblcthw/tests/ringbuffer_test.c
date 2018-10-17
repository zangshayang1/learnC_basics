#include "minunit.h"
#include "../src/lcthw/ringbuffer.h"
#include "../src/lcthw/dbg.h"
#include <assert.h>

char* test_ringbuffer() {
  int rc = -1;

  RingBuffer* rb = RingBuffer_create(100);
  mu_assert(rb != NULL, "Failed to create a ringbuffer.");
  mu_assert(RingBuffer_empty(rb), "Failed to create a ringbuffer correctly.");

  char* data = "Vonvon";

  rc = RingBuffer_write(rb, data, 6);
  mu_assert(rc == 6, "Failed to write.");
  mu_assert(RingBuffer_available_data(rb) == 6, "Failed to write correctly.");
  mu_assert(RingBuffer_available_space(rb) == 94, "Failed to write correctly.");

  char* target = calloc(1, 7); // spare one spot for nullbyte
  rc = RingBuffer_read(rb, target, 6);
  mu_assert(rc == 6, "Failed to read.");
  mu_assert(strcmp(target, data) == 0, "Failed to read correctly.");
  mu_assert(RingBuffer_available_data(rb) == 0, "Failed to read correctly.");
  // when read, start advances to certain amount, if end is met, both of them rewind back to 0.
  mu_assert(RingBuffer_available_space(rb) == 100, "Failed to read correctly.");

  RingBuffer_destroy(rb);

  return NULL;
}

char* all_tests() {
  mu_suite_start();
  mu_run_test(test_ringbuffer);
  return NULL;
}

RUN_TESTS(all_tests);
