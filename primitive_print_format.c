#include <stdio.h>

int main(int argc, char* argv[]) 
{
  int distance = 100;
  float power = 2.345f;
  double super_power = 5678.4321;
  char initial = 'S';
  char firstname[] = "Sean";
  
  printf("You are %d miles away.\n", distance);
  printf("You have %f levels of powers.\n", power);
  printf("You have %f awesome super powers.\n", super_power);
  printf("My initial is %c.\n", initial);
  printf("My first name is %s.\n", firstname);
  
  long large_number = 1L * 1024L * 1024L;
  printf("The world has %ld bugs.\n", large_number);
  printf("That is only a %e portion of the universe.\n", power / large_number);
  
  unsigned long max = 1024L * 1024L * 1024L * 1024L * 1024L * 1024L * 7L - 1L + 1024L * 1024L * 1024L * 1024L * 1024L * 1024L;
  printf("Maximum number in C is: %ld. (64-bit machine)\n", max);
  
  char null_byte = '\0';
  printf("But you care %ld%%.\n", null_byte * large_number);
  
  return 0;
}