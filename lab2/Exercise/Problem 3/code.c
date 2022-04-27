#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#define NUM_THREADS 10
int arr[NUM_THREADS] = {0};

void *hello(void *tid) {
  int index = *((int *)tid);
  printf("Hello from thread %d\n", index);
  arr[index] = 1;
  pthread_exit(NULL);
}

int main() {
  pthread_t tid[NUM_THREADS];
  int i;
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_create(&tid[i], NULL, hello, &i);
    while (arr[i] != 1)
      ;
  }

  pthread_exit(NULL);
}
