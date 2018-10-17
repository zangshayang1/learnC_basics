#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void terminate(const char* msg) {
  if (errno) {
    perror(msg);
  } else {
    printf("Error Message: %s.\n", msg);
  }
  exit(1);
}

// define a function-pointer type that points to a function that takes in 2 int arguements
typedef int (*comparator)(int a, int b);

// define bubble sort that calls a compare function through a pointer, such as *comparator
int* bubble_sort(int* numbers, int count, comparator cpm) {
  int temp;
  int* targets = malloc(count * sizeof(int));
  memcpy(targets, numbers, count * sizeof(int));

  for (int i = 0; i < count; i++) {
    for (int j = 0; j < count - 1; j++) {
      if (cpm(targets[j], targets[j+1]) > 0) {
        temp = targets[j+1];
        targets[j+1] = targets[j];
        targets[j] = temp;
      }
    }
  }
  return targets;
}

int low_to_high(int a, int b) {
  return a - b;
}
int high_to_low(int a, int b) {
  return b - a;
}

int main(int argc, char* argv[]) {
  if (argc < 2) terminate("Please provide at least 1 integers to start sorting, separated by space.");

  int count = argc - 1;
  int* numbers = malloc(count * sizeof(int));
  printf("Input:\n");
  for(int i = 0; i < count; i++) {
    numbers[i] = atoi(argv[i+1]);
    printf("%d\t", numbers[i]);
  }

  printf("\n");

  int* sorted = NULL;
  sorted = bubble_sort(numbers, count, low_to_high);
  for(int i = 0; i < count; i++) {
    printf("%d\t", sorted[i]);
  }

  printf("\n");

  sorted = bubble_sort(numbers, count, high_to_low);
  for(int i = 0; i < count; i++) {
    printf("%d\t", sorted[i]);
  }

  printf("\n");

  free(sorted);
  free(numbers);

  return 0;
}
