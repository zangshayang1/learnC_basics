#include <stdio.h>

int main(int argc, char* argv[]) 
{
  if (argc <= 1) {
    printf("Please enter at least 1 argument.\n");
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    printf("%s\n", argv[i]);
  }
  return 0;
}