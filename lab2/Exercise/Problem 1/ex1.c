#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool alignmentChecking(unsigned int alignment) {
  if (alignment <= 0) {
    return false;
  }
  while (alignment != 1) {
    if (alignment % 2 == 0) {
      alignment /= 2;
      continue;
    }
    return false;
  }
  return true;
}

void *aligned_malloc(unsigned int size, unsigned int alignment) {
  void *p1, *p2;

  p1 = (void *)malloc(size + (size_t)alignment + sizeof(size_t));

  if (size == 0 || p1 == NULL || !alignmentChecking(alignment)) {
    return NULL;
  }

  size_t addr = (size_t)p1 + (size_t)alignment + sizeof(size_t) &
                ~((size_t)alignment - 1);

  p2 = (void *)(addr);

  *((size_t *)p2 - 1) = (size_t)p1;

  return p2;
}

void *aligned_free(void *ptr) {
  free((void *)(*(((size_t *)ptr - 1))));
  return NULL;
}
