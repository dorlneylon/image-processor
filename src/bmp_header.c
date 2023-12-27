#include "bmp_header.h"

struct bmp_header init_header(const struct image *img) {
  return (struct bmp_header){.bfType = BFTYPE,
                             .bfileSize = img->sz + BOFFBITS,
                             .bfReserved = 0,
                             .bOffBits = BOFFBITS,
                             .biSize = BISIZE,
                             .biWidth = img->width,
                             .biHeight = img->height,
                             .biPlanes = BIPLANES,
                             .biBitCount = BIBITCOUNT,
                             .biCompression = BICOMPRESSION,
                             .biSizeImage = BISIZEIMAGE,
                             .biXPelsPerMeter = BIXPELSPERMETER,
                             .biYPelsPerMeter = BIYPELSPERMETER,
                             .biClrUsed = BICLRUSED,
                             .biClrImportant = BICLRIMPORTANT};
}
