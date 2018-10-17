#include <stdio.h>

int main(int argc, char* argv[]) 
{  
  char character = 'c';
  printf("'char character' is a char of size %lu byte.\n", sizeof(character));
  printf("\n");
  
  char* char_ptr = "char_ptr";
  printf("'char* char_ptr' is a pointer to a memory address pointing to a block of memory. The pointer itself takes space of %lu bytes. Now that you assign a c_string of length 8 to the address, printing it as a string will render: '%s', which takes 9 bytes space.\n", sizeof(char_ptr), char_ptr);
  printf("\n");
  
  char char_array[] = {'c', 'h', 'a', 'r', '_', 'a', 'r', 'r', 'a', 'y', '\0'};
  printf("'char char_array[]' is an array of chars of size %lu bytes ('%s') with the last null character being explicitly initialized.\n", sizeof(char_array), char_array);
  printf("\n");
  
  char char_array_str[] = "char_array_str";
  printf("'char char_array_str[]' is an array of chars of size %lu bytes ('%s') initialized as a string literal where the last null_byte is automatically filled.\n", sizeof(char_array_str), char_array_str);
  printf("\n");
  
  char* char_ptr_array[] = {"p1", "p2", "p3"};
  printf("'char* char_ptr_array[]' is an array of pointers respectively pointing to %s, %s, %s, taking space in total %lu bytes for each pointer takes 8 bytes. '[i]' operator advances the pointer for i step and then dereferences it.\n", char_ptr_array[0], char_ptr_array[1], char_ptr_array[2], sizeof(char_ptr_array));
  printf("\n");
  
  char** char_ptr_ptr = char_ptr_array;
  printf("'char** char_ptr_ptr' is a pointer to a char pointer. Advancing the pointer is equivalent to loop through an block of memory (array), such as: %s, %s, %s.\n", *char_ptr_ptr, *(char_ptr_ptr+1), *(char_ptr_ptr+2));
  printf("\n");
  
  return 0;
  
}