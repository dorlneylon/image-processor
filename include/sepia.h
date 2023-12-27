#ifndef SEPIA_H
#define SEPIA_H
#include "image.h"
#include <stdlib.h>
#include <stdint.h>
#include <x86intrin.h>
uint8_t saturation(const uint64_t x);
uint8_t pixel_process(const uint8_t r, const uint8_t g, const uint8_t b);
struct image impl_sepia(struct image const* img);
struct image simd_impl_sepia(struct image img);
// struct image simd_sepia_asm(struct image const* img);
// struct image avx512_impl_sepia(struct image const* img);
#endif // SEPIA_H
