#ifndef COLOR_FUNCTIONS_H_
#define COLOR_FUNCTIONS_H_

#include <stdint.h>

int color_gradient;

uint8_t *norm_escape_stb(int hight, int width, int *escape_ary);
uint8_t *escape_stb_mono(int hight, int width, int *escape_ary);

#endif
