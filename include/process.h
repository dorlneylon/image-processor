#ifndef IMAGE_TRANSFORMER_VIEW_H
#define IMAGE_TRANSFORMER_VIEW_H
#include "io_status.h"
#include "parse.h"
#include "image.h"
#include "sepia.h" // not hehe
#include "rotator.h"
#include <stdlib.h>


int rotate(int argc, char **argv);
int sepia(int WHICH, int argc, char **argv);
int read_response(enum read_status status);
int write_response(enum write_status status);

#endif // IMAGE_TRANSFORMER_VIEW_H
