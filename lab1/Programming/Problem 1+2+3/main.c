#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline/readline.h"
#include "factorial/factorial.h"
#define MAX_LIMIT 50

int main(int argc, char* argv[]) {
   char str[MAX_LIMIT];
   printf("Enter a value: ");
   while(scanf("%s", str)) {
      if (strlen(str) <= MAX_LIMIT) {
         if (read_line(str)) {
            printf("Fatorial(%s): %d\n", str, factorial(atoi(str)));
            break;
         }
         else {
            printf("-1\n");
         }
      }
      else {
         printf("-1\n");
         break;
      }
   }
   return 0;
}
