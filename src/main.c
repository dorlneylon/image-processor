#include "process.h"
#include <stdio.h>

extern void check(void);

int main(int argc, char **argv) {
  (void)argv;
  if (argc != 3 && argc != 4) {
    printf("Usage: ./image_transformer <input file> <output file>\n");
    printf("In case of rotation operation, use: ./image_transformer <input file> <output file> <rotation angle>\n");
    return 0;
  }
  // check();
  return argc == 3 ? sepia(__builtin_cpu_supports("avx2"), argc, argv) : rotate(argc, argv);
}
