#ifndef IMAGE_TRANSFORMER_BMP_HEADER_H
#define IMAGE_TRANSFORMER_BMP_HEADER_H
// bmp_header_view info
#define BFTYPE 19778
#define BFILESIZE 4287252
#define BFRESERVED 0
#define BOFFBITS 54
#define BISIZE 40
#define BIWIDTH 1518
#define BIHEIGHT 941
#define BIPLANES 1
#define BIBITCOUNT 24
#define BICOMPRESSION 0
#define BISIZEIMAGE 4287198
#define BIXPELSPERMETER 2834
#define BIYPELSPERMETER 2834
#define BICLRUSED 0
#define BICLRIMPORTANT 0
#include "image.h"
#include <stdint.h>
#pragma pack(push, 1)
struct bmp_header {
  uint16_t bfType;
  uint32_t bfileSize;
  uint32_t bfReserved;
  uint32_t bOffBits;
  uint32_t biSize;
  uint32_t biWidth;
  uint32_t biHeight;
  uint16_t biPlanes;
  uint16_t biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  uint32_t biXPelsPerMeter;
  uint32_t biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
};
#pragma pack(pop)
struct bmp_header init_header(const struct image *img);

#endif // IMAGE_TRANSFORMER_BMP_HEADER_H
