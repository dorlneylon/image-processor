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

extern void simd_sepia_asm(struct pixel[static 4], struct pixel* result); // 4 pixels at a time

struct image simd_impl_sepia(struct image img) {
  struct image ret = create_image(img.width, img.height);
  if (!ret.data)
    return img;

  uint8_t* cpy = (uint8_t*)(img.data);
  uint8_t* dst = (uint8_t*)(ret.data);

  static const float coef[] = {
    .189f, .686f, .272f, 1,
    .393f, .168f, .534f, 1,
    .769f, .349f, .131f, 1
  };

  for (uint32_t i = 0; i < 3 * img.sz; i += 3) {
    __m128 res;
    __m128 p = _mm_set_ps(cpy[i+2], cpy[i + 1], cpy[i], cpy[i + 3]);
    __m128 q = _mm_load_ps(coef);
    __m128 r = _mm_mul_ps(q, p);
    res = r;
    p = _mm_shuffle_ps(p, p, _MM_SHUFFLE(3, 1, 0, 2));
    q = _mm_load_ps(coef + 4);
    r = _mm_mul_ps(q, p);
    res = _mm_add_ps(res, r);
    p = _mm_shuffle_ps(p, p, _MM_SHUFFLE(3, 1, 0, 2));
    q = _mm_load_ps(coef + 8);
    r = _mm_mul_ps(q, p);
    res = _mm_add_ps(res, r);
    __m128i res_i = _mm_cvtps_epi32(res);
    __m128i res_8 = _mm_packus_epi32(res_i, _mm_setzero_si128());
    uint64_t packed_result = 0;
    packed_result = _mm_cvtsi128_si64(res_8);
    dst[2] = saturation(packed_result & 0xFF);
    dst[1] = saturation((packed_result >> 16) & 0xFF);
    dst[0] = saturation((packed_result >> 32) & 0xFF);
    dst += 3;
  }

  return ret;
}
