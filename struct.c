#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// struct in c is a way to define plain old object
// in c++ it grows more like class
struct Person {
  char* name;
  int age;
};

// check strdup vs strcpy online
char* my_strdup(const char* str) {
  size_t st = strlen(str);
  char* p = malloc(st + 1); // 1 byte for null byte
  assert(p != NULL);
  memcpy(p, str, st + 1); // memcpy(void* dest, const void* src, size_t len);
  return p;
}

// Person must follow struct tag wherever it is declared
struct Person* createPersonInHeap(const char* name, const int age) 
{
  struct Person* p = malloc(sizeof(struct Person));
  assert(p != NULL); // under which circumstances will malloc return NULL ptr?
  p->name = my_strdup(name);
  p->age = age;
  return p;
}
void destroyPersonInHeap(struct Person* who) {
  assert(who != NULL);
  free(who->name); // malloc takes a little more space than declared
  free(who); // free(void* p) uses that metadata to know how much space to free
}

struct Person createPersonInStack(const char* name, const int age) 
{
  struct Person p;
  p.name = my_strdup(name);
  p.age = age;
  return p;
}
void destroyPersonInStack(struct Person p) {
  free(p.name);
}

int printPersonInHeap(struct Person *p) 
{
  printf("%d year-old %s at HEAP address: %p.\n", p->age, p->name, p); // %p for ptr address
  return 0;
}
int printPersonInStack(struct Person p) 
{
  printf("%d year-old %s at STACK address: %p.\n", p.age, p.name, &p); // %p for ptr address
  return 0;
}

int main(int argc, char const *argv[]) {
  
  printf("Constructing each struct Person (skeleton) of size %lu, slightly more than it seems to be (machine-dependent padding mechanism).\n", sizeof(struct Person));
  
  printf("Constructing 'Chch' in HEAP... done.\n");
  struct Person *ch = createPersonInHeap("Chch", 27);
  
  printf("Constructing 'Vonvon' in STACK... done.\n");
  struct Person von = createPersonInStack("Vonvon", 26);
  
  printf("Now...\n");
  printPersonInHeap(ch);
  printPersonInStack(von);
  
  ch->age += 20;
  von.age += 20;
  
  printf("20 years later...\n");
  printPersonInHeap(ch);
  printPersonInStack(von);
  
  printf("free up heap memory... done\n");
  destroyPersonInHeap(ch);
  destroyPersonInStack(von);
  
  return 0;
}