#include <stdio.h>

int system_size() {
  printf("Size of int*: %zu bytes\n", sizeof(int *));
  printf("Size of char*: %zu bytes\n", sizeof(char *));
  printf("Size of void*: %zu bytes\n", sizeof(void *));
  printf("Size of a function pointer: %zu bytes\n", sizeof(void (*)()));
  return 0;
}
