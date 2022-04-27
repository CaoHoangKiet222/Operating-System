#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *malloc(size_t size) {
  void *p;
  p = sbrk(0);
  if (sbrk(size) == (void *)-1) {
    return NULL;
  }
  return p;
}

int main() {
  void *p = malloc(1024);
  printf("%p\n", &p);
}
