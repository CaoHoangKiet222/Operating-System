#include <math.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_THREADS 8
double numPoints;

double randomCoordinates() { return (rand() / (double)RAND_MAX) * 2 - 1; }

void *countPointsInCircle(void *tid) {
  double* numPoints_Per_Thread = (double *)tid;
  double *pointsInCircle = (double *)malloc(sizeof(double));
  *pointsInCircle = 0;

  for (int i = 0; i < *numPoints_Per_Thread; i++) {
    double x = randomCoordinates();
    double y = randomCoordinates();

    if (sqrt(x * x + y * y) <= 1) {
      (*pointsInCircle)++;
    }
  }

  pthread_exit((void *)pointsInCircle);
}

int main(int argc, char *argv[]) {

  clock_t start = clock();

  if (argc != 2) {
    printf("Not enough arguments to do!!!\n");
    exit(-1);
  }
  numPoints = (double)atoi(argv[1]);

  /* Initializing rand() */
  srandom((unsigned)time(NULL));

  pthread_t threads[TOTAL_THREADS];
  void *status;
  double totalPoints = 0;
  double numPoints_Per_Thread;

  printf("Number of threads %d\n", TOTAL_THREADS);
  
  int remainPoints = (int)numPoints % (int)TOTAL_THREADS;
  for (int i = 0; i < TOTAL_THREADS; i++) {
    numPoints_Per_Thread = numPoints / TOTAL_THREADS + (i < remainPoints);
    int rc = pthread_create(&threads[i], NULL, countPointsInCircle, &numPoints_Per_Thread);

    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }

    pthread_join(threads[i], &status);
    totalPoints += *(double *)status;
    free((void *)status);
  }

  printf("Total points random in circle run by mutex_lock %d\n", (int)totalPoints);
  printf("Final Estimation of Pi = %f\n", (4 * totalPoints) / numPoints);

  clock_t end = clock();

  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time %f\n", time_spent / 256);
}
