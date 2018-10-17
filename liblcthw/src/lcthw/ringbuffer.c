#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"
#include "ringbuffer.h"

RingBuffer* RingBuffer_create(int length) {
  RingBuffer* buffer = calloc(1, sizeof(RingBuffer));
  buffer->length = length;
  buffer->start = 0;
  buffer->end = 0;
  buffer->buffer = calloc(buffer->length, 1);
  return buffer;
}

void RingBuffer_destroy(RingBuffer* buffer) {
  if (buffer) {
    free(buffer->buffer);
    free(buffer);
  }
}

int RingBuffer_write(RingBuffer* buffer, char* data, int length) {
  // every time end == start, reset them to 0, so them point to the beginning of the memory chunk
  if (RingBuffer_available_data(buffer) == 0) {
    buffer->start = buffer->end = 0;
  }

  check(length <= RingBuffer_available_space(buffer), \
        "Not enough space: %d request, %d available", \
        RingBuffer_available_data(buffer), length);

  void* result = memcpy(RingBuffer_ends_at(buffer), data, length);
  check(result != NULL, "Failed to write data into buffer.");

  RingBuffer_commit_write(buffer, length);

  return length;

error:
  return -1;
}

int RingBuffer_read(RingBuffer* buffer, char* target, int amount) {
  check(amount <= RingBuffer_available_data(buffer), \
        "Not enough data in the buffer: has %d, needs %d", \
        RingBuffer_available_data(buffer), amount);

  void* result = memcpy(target, RingBuffer_starts_at(buffer), amount);
  check(result != NULL, "Failed to read buffer.");
  target[amount] = '\0'; // set nullbyte

  RingBuffer_commit_read(buffer, amount);

  // every time end == start, reset them to 0, so them point to the beginning of the memory chunk
  if (buffer->end == buffer->start) {
    buffer->start = buffer->end = 0;
  }
  return amount;

error:
  return -1;
}
