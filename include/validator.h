#ifndef IMAGE_TRANSFORMER_VALIDATOR_H
#define IMAGE_TRANSFORMER_VALIDATOR_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool is_num(char *str);
bool is_valid_angle(int16_t ang);
bool is_valid_file(FILE *file);

#endif // IMAGE_TRANSFORMER_VALIDATOR_H
