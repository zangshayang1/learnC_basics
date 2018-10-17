#include <stdio.h>
#include <ctype.h>
#include "dbg.h"
#include <string.h>

int print_message(const char* msg) {
  printf("A STRING: %s\n", msg);
  return 0;
}

int uppercase_message(const char* msg) {
  for (int i = 0; i < strlen(msg); i++) {
    printf("%c\n", toupper(msg[i]));
  }
  printf("\n");
  return 0;
}

int lowercase_message(const char* msg) {
  for (int i = 0; i < strlen(msg); i++) {
    printf("%c\n", tolower(msg[i]));
  }
  printf("\n");
  return 0;
}

int fail_on_purpose(const char* msg) {
  return 1;
}
