#include <stdio.h>

/*
 C passing variable by value.
*/

// define a pointer to function that changes the content of a given array
typedef void (*change)(int* numbers);

void printArray(int* numbers, int len) {
  for(int i = 0; i < len; i++) {
    printf("%d\t", numbers[i]);
  }
  printf("\n");
}

void apply(int* numbers, int len, change func) {
  func(numbers);
  printArray(numbers, len);
}
void change_1(int* numbers) {
  numbers[0] = 0;
}
void change_2(int* numbers) {
  int tmp[] = {1, 0, 3, 4, 5};
  numbers = tmp;
}

void applyChange3(int** numbers, int len) {
  int tmp[] = {1, 2, 0, 4, 5};
  *numbers = tmp;
  printArray(*numbers, len);
}

int main(int argc, char* argv[]) {

  int origin[] = {1, 2, 3, 4, 5};
  int cp1[] = {1, 2, 3, 4, 5};
  int cp2[] = {1, 2, 3, 4, 5};
  int cp3[] = {1, 2, 3, 4, 5};
  int len = 5;

  printf("Origin array:\n");
  printArray(origin, len);

  printf("Apply change_1...Works! Directly modifying the value at the address.\n");
  apply(cp1, len, change_1);

  printf("Apply change_2...Failed! Try to modify the address of a variable. Because C always passes variable by value and the variable in the 'change_2' function is just a copy, although they hold the same address.\n");
  apply(cp2, len, change_2);

  printf("Apply change_3...Works! Pass in a pointer1 to a pointer2 to a value and change the value of pointer1, making it point at some other address, which holds a new value.\n");
  int* pt = &cp3[0];
  int** ppt = &pt;
  applyChange3(ppt, len);

  return 0;
}
