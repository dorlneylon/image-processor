#include "process.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 3 && argc != 4) {
    printf("Usage: ./image_transformer <input file> <output file>\n");
    printf("In case of rotation operation, use: ./image_transformer <input file> <output file> <rotation angle>\n");
    return 0;
  }
  return argc == 3 ? sepia(0, argc, argv) : rotate(argc, argv);
}
