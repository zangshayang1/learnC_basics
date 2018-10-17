#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "dbg.h"

/*
  Pay attention to how VarArgs are used.
*/

#define MAX_DATA 100

int read_string(char** out_string, int max_buffer) { // notice the ** for carrying target out of the function
  *out_string = calloc(1, max_buffer + 1);
  check_mem(*out_string);

  char* ret = fgets(*out_string, max_buffer, stdin);
  check(ret != NULL, "Input Error.");

  return 0;

error:
  if (*out_string) free(*out_string);
  *out_string = NULL;
  return -1;
}

int remove_trailing_newline_character(char** input) {
  check(*input != NULL, "Invalid Input.");
  for(int i = 0; i < strlen(*input); i++) {
    if (*input[i] == '\n') {
      *input[i] = '\0';
    }
  }
  return 0;
error:
  return -1;
}

int read_int(int* out_int, int max_buffer) {
  char* input = NULL;
  int rc = read_string(&input, max_buffer);
  check(rc == 0, "Failed to read from stdin.");
  *out_int = atoi(input);
  free(input);
  return 0;

error:
  if (input) free(input);
  return -1;
}

/*
* my_scanf
*
* @Param const char* fmt, such as "%s", "%c", "%d"
*/
int my_scanf(const char* fmt, ...) {

  int* out_int = NULL;
  char* out_char = NULL;
  char** out_string = NULL;
  int max_buffer = 0;
  int rc = -1;

  va_list argp; // arguments pointer
  va_start(argp, fmt); // initialize argp;

  check(strlen(fmt) == 2 && fmt[0] == '%', "Invalid Input.");

  switch (fmt[1]) {
    case 'c':
      max_buffer = va_arg(argp, int);
      out_char = va_arg(argp, char*); // <stdarg.h>: va_arg(va_list argp, TYPE)
      out_string = va_arg(argp, char**);
      rc = read_string(out_string, max_buffer);
      *out_char = **out_string;
      break;

    case 's':
      max_buffer = va_arg(argp, int);
      out_string = va_arg(argp, char**);
      rc = read_string(out_string, max_buffer);
      check(rc == 0, "Failed to read string.");
      break;

    case 'd':
      max_buffer = va_arg(argp, int);
      out_int = va_arg(argp, int*);
      rc = read_int(out_int, max_buffer);
      check(rc == 0, "Failed to read int.");
      break;

    default:
      sentinel("Format Not Supported.");
  }
  va_end(argp);
  return 0;

error:
  va_end(argp);
  return -1;
}

int main(int argc, char* argv[]) {

  char* first_name = NULL;
  char initial = ' ';
  char* temp = NULL;
  int age = 0;

  printf("Please enter your first name:\n");
  my_scanf("%s", MAX_DATA, &first_name);
  printf("Your first name is: %s\n", first_name);

  printf("Please enter your initial:\n");
  my_scanf("%c", MAX_DATA, &initial, &temp);
  printf("Your initial is: %c\n", initial);

  printf("Please enter your age:\n");
  my_scanf("%d", MAX_DATA, &age);
  printf("You age is %d\n", age);

  free(first_name);
  return 0;

error:
  return -1;
}
