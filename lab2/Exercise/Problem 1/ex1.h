#include <stdbool.h>
#ifndef EX1_H
#define EX1_H

bool alignmentChecking(unsigned int alignment);
void *aligned_malloc(unsigned int size, unsigned int alignment);
void *aligned_free(void *ptr);

#endif
