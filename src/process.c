#include "process.h"
#include "sepia.h"
#include <stdio.h>

int rotate(int argc, char **argv) {
  int16_t ang = 0;
  struct image img = {0};
  enum read_status response_status = parse_input(argc, argv, ROTATE_TYPE, &ang);

  if (response_status)
    return read_response(response_status);

  FILE *in = NULL;
  response_status = open_file(argv[1], "rb", &in);
  if (response_status)
    return read_response(response_status);

  response_status = from_bmp(in, &img);
  if (response_status) {
    clear_image(&img);
    return read_response(response_status);
  }
  rotate_image(&img, ang);

  FILE *out = NULL;
  response_status = open_file(argv[2], "wb", &out);
  if (response_status) {
    clear_image(&img);
    return read_response(response_status);
  }

  enum write_status write_response_status = to_bmp(out, &img);
  if (write_response_status) {
    clear_image(&img);
    return write_response(write_response_status);
  }
  clear_image(&img);

  return read_response(response_status);
}

int sepia(int WHICH, int argc, char **argv) {
  struct image img = {0};
  enum read_status response_status = parse_input(argc, argv, SEPIA_TYPE, NULL);
  if (response_status)
    return read_response(response_status);

  FILE *in = NULL;
  response_status = open_file(argv[1], "rb", &in);
  if (response_status)
    return read_response(response_status);

  response_status = from_bmp(in, &img);
  if (response_status) {
    clear_image(&img);
    return read_response(response_status);
  }

  struct image tmp = WHICH ? simd_impl_sepia(img) : impl_sepia(&img);
  clear_image(&img);
  img = tmp;

  FILE *out = NULL;
  response_status = open_file(argv[2], "wb", &out);
  if (response_status) {
    clear_image(&img);
    return read_response(response_status);
  }

  enum write_status write_response_status = to_bmp(out, &img);
  if (write_response_status) {
    clear_image(&img);
    return write_response(write_response_status);
  }
  
  clear_image(&img);
  return read_response(response_status);
}

int read_response(enum read_status status) {
  switch (status) {
  case READ_OK:
    return EXIT_SUCCESS;
  case READ_INVALID_DATA:
    printf("Invalid data\n");
    return EXIT_FAILURE;
  case READ_INVALID_FILENAME:
    printf("Invalid filename\n");
    return EXIT_FAILURE;
  case READ_INVALID_HEADER:
    printf("Invalid header\n");
    return EXIT_FAILURE;
  case READ_INVALID_SIGNATURE:
    printf("Invalid signature\n");
    return EXIT_FAILURE;
  case READ_UNEXPECTED_EOF:
    printf("Unexpected EOF\n");
    return EXIT_FAILURE;
  case READ_ERROR:
    printf("Error\n");
    return EXIT_FAILURE;
  default:
    printf("Unknown error\n");
    return EXIT_FAILURE;
  }
}

int write_response(enum write_status status) {
  switch (status) {
  case WRITE_OK:
    return EXIT_SUCCESS;
  case WRITE_INVALID_FILENAME:
    printf("Invalid filename\n");
    return EXIT_FAILURE;
  case WRITE_CREATE_ERROR:
    printf("Can't create file\n");
    return EXIT_FAILURE;
  case WRITE_HEADER_ERROR:
    printf("Can't write header\n");
    return EXIT_FAILURE;
  case WRITE_ERROR:
    printf("Error\n");
    return EXIT_FAILURE;
  default:
    printf("Unknown error\n");
    return EXIT_FAILURE;
  }
}
