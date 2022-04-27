#include "ex1.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  void *p = aligned_malloc(16, 64);
  printf("Address of p %p\n", p);
  aligned_free(p);
}
