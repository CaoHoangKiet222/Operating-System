#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_LINE_LENGTH 50

void countDivisibleNumbers(const int* arr, const int size, int* num1, const int dvBy) {
    for (int i = 0; i < size; i++) {
       if (arr[i] % dvBy == 0) (*num1)++;
    }
    return;
}

int main(int argc, char **argv)
{
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int sizeArr = 0;
    int arr[MAX_LINE_LENGTH], num1 = 0;
    
    FILE *file = fopen("numbers.txt", "r");
    
    if (!file)
    {
        perror("numbers.txt");
        return EXIT_FAILURE;
    }
    
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
       sizeArr++;
       arr[sizeArr-1] = atoi(line);
    }

    if (fclose(file))
    {
        return EXIT_FAILURE;
        perror("numbers.txt");
    }

   pid_t child_pid;
   child_pid = fork();

   if (child_pid == -1) {
      perror("Fork failed");
      exit(1);
   }

   if (child_pid == 0) {
      countDivisibleNumbers(arr, sizeArr, &num1, 3);
      num1 != 0 ? printf("%d\n", num1) : -1;
      fflush(stdout);
   }
   else {
      wait(NULL);
      countDivisibleNumbers(arr, sizeArr, &num1, 2);
      num1 != 0 ? printf("%d\n", num1) : -1;
      fflush(stdout);
   }
}
