#include <stdio.h>
#include "dbg.h"

#define MAX_DATA 100

/*
  fscanf
  fgets
  fgetc
  fopen
  freopen
  fdopen
  fclose
  fcloseall
  fgetpos
  fseek
  ftell
  rewind
  fprintf
  fwrite
  fread
*/

char* EYE_COLORS[] = {"BLUE", "GREEN", "BROWN", "BLACK", "OTHER"};

typedef enum EyeColor {
  BLUE, GREEN, BROWN, BLACK, OTHER
} EyeColor;

typedef struct Person {
  int age;
  char first_name[MAX_DATA];
  EyeColor eyeColor;
} Person;

void printPerson(struct Person p) {
  printf("Name: %s\t Age: %d\t Eye Color: %s\n", p.first_name, p.age, EYE_COLORS[p.eyeColor]);
}

int main(int argc, char* argv[]) {
  Person p;

  printf("What is your first name?\n");
  char* in = fgets(p.first_name, MAX_DATA - 1, stdin); // get from stdin, capped by MAX_DATA or '\n'
  check(in != NULL, "Failed to read first name."); // in holds the content, including '\n' at the end, '\0' automatically appended.

  printf("How old are you?\n");

  int rc = fscanf(stdin, "%d", &p.age);
  check(rc > 0, "You have to enter an integer.");

  printf("What color are your eyes?\n");

  for(int i = 0; i < OTHER + 1; i++) {
    printf("%d) %s\n", i, EYE_COLORS[i]);
  }
  printf("> ");

  int eyeColor = -1;
  rc = fscanf(stdin, "%d", &eyeColor);
  check(eyeColor <= OTHER && eyeColor >= 0, "Please enter a correct number.");
  p.eyeColor = eyeColor;

  printf("------ SUMMARY ------\n");

  printPerson(p);

  return 0;

error:
  return -1;
}
