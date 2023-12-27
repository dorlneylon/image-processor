#include "image.h"

struct image init_img(uint32_t w, uint32_t h, struct pixel *p) {
  struct image img = {.height = h, .width = w, .data = p};
  _calc_img_sz(&img);
  return img;
}
struct image create_image(uint32_t w, uint32_t h){
    return (struct image){
        .height = h,
        .width = w,
        .data = malloc(w * h * sizeof(struct pixel)),
        .sz = w * h,
    };
}
void _calc_img_sz(struct image *img) { img->sz = img->height * img->width; }
void clear_image(struct image *img){
    if(img != NULL){
        free(img->data);
    }
}
