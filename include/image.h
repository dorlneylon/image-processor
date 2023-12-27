#ifndef IMAGE_TRANSFORMER_IMAGE_H
#define IMAGE_TRANSFORMER_IMAGE_H
#include "pixel.h"

#include <stdint.h>
#include <stdlib.h>


struct image {
  uint32_t height, width, sz;
  struct pixel *data;
};

struct image init_img(uint32_t w, uint32_t h, struct pixel *p);
void _calc_img_sz(struct image *img);
struct image create_image(uint32_t w, uint32_t h);
void clear_image(struct image *img);
#endif // IMAGE_TRANSFORMER_IMAGE_H
