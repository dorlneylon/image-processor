#include "rotator.h"
#include <math.h>

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

static struct image rotate_arbitary(const struct image source, int32_t ang) {
  double rad_angle = ang * M_PI / 180.0;

  int32_t new_width = (int32_t)(fabs(source.width * cos(rad_angle)) + fabs(source.height * sin(rad_angle)));
  int32_t new_height = (int32_t)(fabs(source.width * sin(rad_angle)) + fabs(source.height * cos(rad_angle)));

  struct image new_image = create_image(new_width, new_height);
  if (!new_image.data)
    return new_image;

  for (uint32_t i = 0; i < new_image.height; i++) {
    for (uint32_t j = 0; j < new_image.width; j++) {
      int32_t orig_x = j - new_width / 2;
      int32_t orig_y = i - new_height / 2;
      int32_t rotated_x = (int32_t)(orig_x * cos(rad_angle) - orig_y * sin(rad_angle));
      int32_t rotated_y = (int32_t)(orig_x * sin(rad_angle) + orig_y * cos(rad_angle));
      int32_t src_x = rotated_x + source.width / 2;
      int32_t src_y = rotated_y + source.height / 2;
      if (src_x >= 0 && src_x < (int32_t)source.width && src_y >= 0 && src_y < (int32_t)source.height) {
        new_image.data[i * new_image.width + j] = source.data[src_y * source.width + src_x];
      }
    }
  }

  return new_image;
}

void rotate_image(struct image *img, int32_t angle) {
  if (angle % 90 != 0) {
    struct image rotd = rotate_arbitary(*img, angle);
    clear_image(img);
    *img = rotd;
    return;
  }
  angle = angle_convert(-angle);
  struct image rotated = {0};
  for (int32_t a = 0; a < angle; a += 90) {
    rotated = rotate90(*img);
    clear_image(img);
    *img = rotated;
  }
}
