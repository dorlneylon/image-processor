#include "validator.h"
#include <ctype.h>

bool is_num(char *str) {
  if (!str)
    return false;
  int8_t startpos = 0;
  if (str[0] == '-')
    startpos = 1;
  for (int8_t i = startpos; str[i] != '\0'; i++)
    if (!isdigit(str[i]))
      return false;
  return true;
}

bool is_valid_angle(int16_t ang) { return ang <= 270 && ang >= -270; }

bool is_valid_file(FILE *file) {
  if (!file)
    return false;
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);
  return size > 0;
}
