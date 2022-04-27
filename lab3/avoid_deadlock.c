#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define MAX_ITEMS 10
#define THREADS 2
#define LOOPS 2*MAX_ITEMS

int buffer [MAX_ITEMS]; 
int fill = 0;
int use = 0; 

sem_t empty;
sem_t full;
sem_t lock;

void put(int value); 
int get (); 

void *producer(void *arg) {
    int i;
    int tid = (int)arg;
    printf( "Producer %d run\n" , tid);
    for (i = 0; i < LOOPS; i++) {
         sem_wait(&empty);           // line p1
         sem_wait(&lock);           // line p0 (NEW LINE)
         printf( "Producer %d put data %d\n" , tid , i);
         put(i);                     // line p2
        // printf( "Fill %d\n" , fill);
         sleep(1);
         sem_post(&lock);           // line p4 (NEW LINE)
         // printf( "Producer %d post lock\n" , tid);
         sem_post(&full);            // line p3
         // printf( "Producer %d post full\n" , tid);
   }
  pthread_exit(NULL);
}

 void *consumer(void *arg) {
     int i, tmp = 0;
     int tid = (int)arg;
    printf( "Consumer %d run\n" , tid);
      while(tmp != -1) {
         sem_wait(&full);            // line c1
         sem_wait(&lock);           // line c0 (NEW LINE)
         printf ( "Consumer %d get data %d\n" , tid, tmp);
         tmp = get();            // line c2
        // printf( "Use %d\n" , use);
         sleep(1);
         sem_post(&lock);           // line c4 (NEW LINE)
         // printf( "Consumer %d unlock\n" , tid);
         sem_post(&empty);           // line c3
         // printf( "Consumer %d post empty\n" , tid);
     }
  pthread_exit(NULL);
 }

int main(int argc, char *argv[]) {
  int i, j;
  int tid[THREADS];
  pthread_t producers[THREADS];
  pthread_t consumers[THREADS];

  sem_init(&empty, 0, MAX_ITEMS);
  sem_init(&full, 0, 0);
   sem_init(&lock, 0, 1);   //lockmutex=1 because it is a lock (NEW LINE)

  for (i = 0; i < THREADS; i++) {
    tid[i] = i;
    pthread_create(&producers[i], NULL, producer, (void*) tid[i]);
    pthread_create(&consumers[i], NULL, consumer, (void*) tid[i]);
  }

  for (i = 0; i < THREADS; i++) {
    tid[i] = i;
    pthread_join(producers[i], NULL);
    pthread_join(consumers[i], NULL);
  }

  sem_destroy(&full);
  sem_destroy(&empty);
  sem_destroy(&lock);
  return 0;
}

void put(int value){
  buffer[fill] = value;
  fill = (fill + 1) % MAX_ITEMS;
}

int get(){
  int tmp = buffer[use];
  use = (use + 1) % MAX_ITEMS;
  return tmp;
}
