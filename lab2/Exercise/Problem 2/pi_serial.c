#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double randomCoordinates() { return (rand() / (double)RAND_MAX) * 2 - 1; }

int main(int argc, char *argv[]) {
  clock_t start = clock();

  double pointsInCircle = 0;

  if (argc != 2) {
    printf("Not enough arguments to do!!!\n");
    exit(1);
  }
  double numPoints = (double)atoi(argv[1]);

  /* Initializing rand() */
  srandom((unsigned)time(NULL));

  for (int i = 0; i < (int)numPoints; i++) {
    double x = randomCoordinates();
    double y = randomCoordinates();

    if (sqrt(x * x + y * y) <= 1) {
      pointsInCircle++;
    }
  }

  printf("Final Estimation of Pi = %f\n", (4 * pointsInCircle) / numPoints);

  clock_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time %f\n", time_spent / 256);
}
