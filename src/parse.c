#include "parse.h"
#include "io_status.h"
#include "validator.h"
#include "image.h"
#include "pixel.h"
const size_t PIXEL_BYTE_SIZE = 3;
static inline uint32_t calc_padding(uint32_t size) {
  return (4 - size % 4) % 4;
}

enum read_status parse_input(const int argc, char **restrict argv, enum request_type request,
                             int16_t *ang) {
  if (request == SEPIA_TYPE && argc == 3)
    return READ_OK;
  if (request != ROTATE_TYPE || argc != 4 || !is_num(argv[3]))
    return READ_INVALID_DATA;

  *ang = (int16_t)atoi(argv[3]);
  if (!is_valid_angle(*ang))
    return READ_INVALID_DATA;

  return READ_OK;
}

enum read_status open_file(char const* restrict filename,
  char const* restrict mode, FILE** file) {
  if (!filename)
    return READ_INVALID_DATA;
  *file = fopen(filename, mode);
  return READ_OK;
}

enum read_status from_bmp(FILE *file, struct image *img) {
  struct bmp_header header;
  if (!is_valid_file(file)) {
    return READ_ERROR;
  }
  if (fread(&header, sizeof(struct bmp_header), 1, file) != 1 ||
      header.bfType != 0x4D42)
    return READ_INVALID_HEADER;
  *img = create_image(header.biWidth, header.biHeight);
  if (img->data == NULL) {
    return READ_CANNOT_ALLOCATE;
  }
  uint32_t padding = calc_padding(header.biWidth * sizeof(struct pixel));

  for (uint32_t i = 0; i < header.biHeight; ++i) {
    if (fread(img->data + header.biWidth * i,
              sizeof(struct pixel) * header.biWidth, 1, file) != 1)
      return READ_INVALID_DATA;
    if (fseek(file, padding, SEEK_CUR))

      return READ_INVALID_DATA;
  }

  return READ_OK;
}

enum write_status to_bmp(FILE *file, struct image const *img) {
  struct bmp_header header = init_header(img);
  if (fwrite(&header, sizeof(header), 1, file) != 1)
    return WRITE_ERROR;
  uint8_t padding_array[4] = {0,0,0,0};
  uint32_t padding = calc_padding(header.biWidth * sizeof(struct pixel));
  for (size_t i = 0; i < header.biHeight; ++i) {
    if (fwrite(img->data + img->width * i,
               (size_t)img->width * sizeof(struct pixel), 1, file) < 1)
      return WRITE_ERROR;
    if (padding) {
      if (fwrite(&padding_array, padding, 1, file) !=
          1) {
        return WRITE_ERROR;
      }
    }
  }

  return WRITE_OK;
}
