#ifndef IMAGE_TRANSFORMER_ROTATOR_H
#define IMAGE_TRANSFORMER_ROTATOR_H
#include "image.h"

#include "pixel.h"
#include <stdint.h>
#include <stdio.h>
// static struct image rotate90(const struct image source);
void rotate_image(struct image *img, int32_t angle);
#endif // IMAGE_TRANSFORMER_ROTATOR_H
