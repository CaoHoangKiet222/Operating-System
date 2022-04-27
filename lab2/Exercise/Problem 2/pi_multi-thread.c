#include <math.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_THREADS 100
double numPoints;

double randomCoordinates() { return (rand() / (double)RAND_MAX) * 2 - 1; }

void *countPointsInCircle(void *tid) {
  double *pointsInCircle = (double *)malloc(sizeof(double));
  *pointsInCircle = 0;

  /* printf("%d\n", *((int *)tid)); */
  int id = *(int *)tid;

  double numPoints_Per_Thread = numPoints / TOTAL_THREADS;
  /* printf("%f\n", numPoints_Per_Thread); */

  for (int i = 0; i < numPoints_Per_Thread; i++) {
    double x = randomCoordinates();
    double y = randomCoordinates();
    /* printf("x = %f\n", (double)x); */
    /* printf("y = %f\n", (double)y); */

    if (sqrt(x * x + y * y) <= 1) {
      (*pointsInCircle)++;
    }
  }

  if (id == TOTAL_THREADS - 1) {
    double remainPoints = (int)numPoints % (int)TOTAL_THREADS;
    for (int i = 0; i < remainPoints; i++) {
      double x = randomCoordinates();
      double y = randomCoordinates();

      if (sqrt(x * x + y * y) <= 1) {
        (*pointsInCircle)++;
      }
    }
  }

  /* printf("points in circle %f\n", *(double *)pointsInCircle); */
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

  for (int i = 0; i < TOTAL_THREADS; i++) {
    int rc = pthread_create(&threads[i], NULL, countPointsInCircle, &i);

    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }

    pthread_join(threads[i], &status);
    totalPoints += *(double *)status;
    free((void *)status);
  }

  printf("Final Estimation of Pi = %f\n", (4 * totalPoints) / numPoints);

  clock_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time %f\n", time_spent / 256);
}
