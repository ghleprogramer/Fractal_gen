#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "../include/range_to_list.h"
#include "../include/color_functions.h"

double color_range[] = {0, 255};
int color_var = 65;

uint8_t *norm_escape_stb(int hight, int width, int *escape_ary)
{
	double *color_ary = length_rangelist(color_range, color_var);

	uint8_t *stb_ary = calloc(hight * width * 3, sizeof(uint8_t));
	if (stb_ary == NULL || color_ary == NULL) {
		return NULL;
	}

	int stb_indx = 0;
	for (int i = 0; i < hight * width; i++)
	{
		int color = round(color_ary[escape_ary[i] % color_var]);
		stb_ary[stb_indx] = color;
		stb_indx++;
		stb_ary[stb_indx] = color;
		stb_indx++;
		stb_ary[stb_indx] = color;
		stb_indx++;
	}

	free(color_ary);
	return stb_ary;
}

uint8_t *escape_stb_mono(int hight, int width, int *escape_ary)
{
	uint8_t *stb_mono_ary = calloc(hight * width, sizeof(uint8_t));
	if (stb_mono_ary == NULL) {
		return NULL;
	}

	for (int i = 0; i < hight * width; i++)
	{
		if (escape_ary[i] % 2) {
			stb_mono_ary[i] = 0xff;
		}
	}

	return stb_mono_ary;
}
