#include "sepia.h"
#include "image.h"
#include "pixel.h"
#include <stdint.h>

inline uint8_t saturation(const uint64_t x) { return x < 256 ? x : 255; }

const float c[3][3] = {
    {.393f, .769f, .189f}, {.349f, .686f, .168f}, {.272f, .534f, .131f}};

struct image impl_sepia(struct image const *img) {
  struct image new_image = create_image(img->width, img->height);
  if (!new_image.data)
    return *img;

  for (uint32_t i = 0; i < img->height; ++i) {
    for (uint32_t j = 0; j < img->width; ++j) {
      struct pixel p = (struct pixel){
          .r = saturation(c[0][0] * img->data[i * img->width + j].r +
                          c[0][1] * img->data[i * img->width + j].g +
                          c[0][2] * img->data[i * img->width + j].b),
          .g = saturation(c[1][0] * img->data[i * img->width + j].r +
                          c[1][1] * img->data[i * img->width + j].g +
                          c[1][2] * img->data[i * img->width + j].b),
          .b = saturation(c[2][0] * img->data[i * img->width + j].r +
                          c[2][1] * img->data[i * img->width + j].g +
                          c[2][2] * img->data[i * img->width + j].b)};
      new_image.data[i * img->width + j] = p;
    }
  }

  return new_image;
}

extern void sepia_asm(uint8_t* src, uint8_t* result, uint32_t sz);

struct image simd_impl_sepia(struct image img) {
  struct image ret = create_image(img.width, img.height);
  if (!ret.data)
    return img;
  
  sepia_asm((uint8_t*)img.data, (uint8_t*)ret.data, 3*img.sz);
  return ret;
}
