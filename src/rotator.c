#include "rotator.h"

static int32_t angle_convert(int32_t angle) {
  angle = ((angle % 360) + 360) % 360;
  return angle;
}

static struct image rotate90(const struct image source) {
    struct image new_image = create_image(source.height, source.width);
    if (!new_image.data)
        return new_image;
    for(uint32_t i = 0; i < source.height; i++)
        for(uint32_t j = 1; j <= source.width; j++)
            new_image.data[j * source.height - i - 1] = source.data[i * (source.width) + j - 1];
    return new_image;
}

void rotate_image(struct image *img, int32_t angle) {
  angle = angle_convert(-angle);
  struct image rotated = {0};
  for (int32_t a = 0; a < angle; a += 90) {
    rotated = rotate90(*img);
    clear_image(img);
    *img = rotated;
  }
}
