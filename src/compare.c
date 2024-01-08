#include "process.h"
#include <time.h>

void check(void) {
  char **argv = (char**)malloc(3 * sizeof(char*));
  argv[0] = "process";
  argv[1] = "A.bmp";
  argv[2] = "output.bmp";

  struct image img = {0};
  enum read_status response_status = parse_input(3, argv, SEPIA_TYPE, NULL);
  if (response_status)
    return;

  FILE *in = NULL;
  response_status = open_file(argv[1], "rb", &in);
  if (response_status)
    return;

  response_status = from_bmp(in, &img);
  if (response_status) {
    clear_image(&img);
    return;
  }

  clock_t tstart = clock();

  for (int i = 0; i < 5; ++i) {
    struct image tmp = impl_sepia(&img);
    (void)tmp;
  }

  clock_t tend = clock();
  printf("%f\n", (double)(tend - tstart) / CLOCKS_PER_SEC);

  tstart = clock();

  for (int i = 0; i < 5; ++i) {
    struct image tmp = simd_impl_sepia(img);
    (void)tmp;
  }

  tend = clock();
  printf("%f\n", (double)(tend - tstart) / CLOCKS_PER_SEC);
}
