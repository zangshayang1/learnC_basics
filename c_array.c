#include <stdio.h>

int main(int argc, char* argv[])
{
  int numbers[4] = {1};
  char characters[4] = {'a'};
  
  printf("How C init an array of int ?\n");
  printf("%d\t%d\t%d\t%d\n", numbers[0], numbers[1], numbers[2], numbers[3]);
  
  printf("How C init an array of char ?\n");
  printf("%c\t%c\t%c\t%c\t\n", characters[0], characters[1], characters[2], characters[3]);
  
  printf("How C prints an array of char as a string ?\n");
  printf("%s\n", characters);
  
  printf("Setting array of chars...\n");
  characters[0] = 'S';
  characters[1] = 'e';
  characters[2] = 'a';
  characters[3] = '\0';
  
  printf("Now the string is %s\n", characters);
  
  printf("Don't forget null byte '\\0' closing the string.\n");
  char four_bytes[4] = "Sean";
  printf("Otherwise, %s happens.\n", four_bytes);
  
  printf("Another way to set up array of chars is using pointer.\n");
  
  char* ptr = "Von";
  printf("Print char pointer one by one: %c\t%c\t%c\t\n", ptr[0], ptr[1], ptr[2]);
  printf("Print char pointer as a string: %s\n", ptr);
  
  printf("Assigning chars into an array of int...\n");
  int temp_numbers[4];
  for (int i = 0; i < 4; i++) {
    temp_numbers[i] = characters[i];
  }
  printf("%d\t%d\t%d\t%d\n", temp_numbers[0], temp_numbers[1], temp_numbers[2], temp_numbers[3]);
  
  printf("Assigning numbers into an array of char...\n");
  numbers[0] = 65;
  numbers[1] = 0;
  numbers[2] = 230;
  numbers[3] = 128 * 10 + 65;
  printf("%d\t%d\t%d\t%d\t\n", numbers[0], numbers[1], numbers[2], numbers[3]);
  char temp_chars[4];
  for (int i = 0; i < 4; i++) {
    temp_chars[i] = numbers[i];
  }
  printf("%c\t%c\t%c\t%c\t\n", temp_chars[0], temp_chars[1], temp_chars[2], temp_chars[3]);
  
  printf("What if I take the four bytes char array as a number?\n");
  printf("%d\n", (int) characters);
  
  return 0;
}