#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static volatile int balance = 0;
pthread_mutex_t lock;

void *mythread(void *arg) {
        char *letter = arg;
  printf("%s: begin\n", letter);

  pthread_mutex_lock(&lock);
  int i;
  for (i = 0; i < 1e7; i++) {
    balance = balance + 1;
  }
  printf("%s: done with balance %d\n", letter, balance);
  pthread_mutex_unlock(&lock);

  printf("%s: done\n", letter);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t p1, p2, p3;
  int rc;
  pthread_mutex_init(&lock, NULL);
  printf("main: begin [balance = %d]\n", balance);

  rc = pthread_create(&p1, NULL, mythread, "A");
  assert(rc == 0);
  rc = pthread_create(&p2, NULL, mythread, "B");
  assert(rc == 0);
  rc = pthread_create(&p3, NULL, mythread, "C");
  assert(rc == 0);

  // join waits for the threads to finish
  pthread_join(p1, NULL);
  assert(rc == 0);
  pthread_join(p2, NULL);
  assert(rc == 0);
  pthread_join(p3, NULL);
  assert(rc == 0);

  printf("main: done with both [balance = %d]\n", balance);
  return 0;
}
