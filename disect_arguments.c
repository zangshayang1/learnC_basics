#include <stdio.h>

// forward declaration
int disect(const int argc, char* argv[]);

int main(int argc, char* argv[]) 
{
  if (argc <= 1) {
    printf("Please enter at least one argument.\n");
    return 1;
  }
  disect(argc, argv);
  return 0;
}

int disect(const int argc, char* argv[])
{
  for (int i = 1; i < argc; i++) {
    char* p = argv[i];
    while (*p != '\0') {
      printf("%c => %d \n", *p, *p);
      p++;
    }
  }
  return 0;
}