#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
   size_t MB = 1024 * 1024;
   size_t maxMB = 0;
   void *ptr = NULL;

   do {
      if (ptr != NULL) {
         printf("Bytes of memory checked = %zi\n", maxMB);
         memset(ptr, 0, maxMB);
      }
      maxMB += MB;
      ptr = malloc(maxMB);
      printf("%d\n", *(size_t *)ptr);
   } while(ptr != NULL);

   return 0;
}
