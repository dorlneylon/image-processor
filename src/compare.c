#include "io_status.h"
#include "process.h"
#include "sepia.h"
#include <bits/time.h>
#include <time.h>

void check(void) {
  char **argv = (char**)malloc(3 * sizeof(char*));
  argv[0] = "process";
  argv[1] = "asdasd.bmp";
  argv[2] = "output.bmp";


  struct timespec start, start2, end;
  clock_gettime(CLOCK_REALTIME, &start);

  for (int i = 0; i < 100; ++i) {
    int nok = sepia(1, 3, argv);
    if (nok) {
      printf("KOSHMAR %d", i);
      return;
    }
  }

  clock_gettime(CLOCK_REALTIME, &end);

  printf("No SSE instructions: %f\n", (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);
  clock_gettime(CLOCK_REALTIME, &start2);


  for (int i = 0; i < 100; ++i) {
    int nok = sepia(1, 3, argv);
    if (nok) {
      printf("KOSHMAR 2 %d", i);
      return;
    }
  }

  clock_gettime(CLOCK_REALTIME, &end);

  printf("With SSE instructions: %f\n", (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);
}

/*int main(void) {
  check();
  return 0;
}*/
