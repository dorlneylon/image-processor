#ifndef IMAGE_TRANSFORMER_BMP_MAPPER_H
#define IMAGE_TRANSFORMER_BMP_MAPPER_H
#include "bmp_header.h"
#include "io_status.h"
#include "image.h"
#include <stdio.h>

enum read_status parse_input(const int argc, char **__restrict__ argv, enum request_type request,
                             int16_t *ang);
enum read_status from_bmp(FILE *file, struct image *img);
enum write_status to_bmp(FILE *file, struct image const *img);
enum read_status open_file(char const *__restrict__ filename,
                           char const *__restrict__ mode, FILE **file);

#endif // IMAGE_TRANSFORMER_BMP_MAPPER_H
