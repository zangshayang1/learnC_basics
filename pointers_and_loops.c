#include <stdio.h>
#include <string.h>

int main()
{
  int num_arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
  char* str_arr[] = {"Sean", "Jon", "Vonvon", "Chch"};
  
  // use [] operator to loop through 2D array
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d\t", num_arr[i][j]);
    }
    printf("\n");
  }
  
  // use pointer to loop through 2D array
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < strlen(str_arr[i]); j++) {
      printf("%c\t", str_arr[i][j]);
    }
    printf("\n");
  }
  
  return 0;
}