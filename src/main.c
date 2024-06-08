// a program for creating fractal images

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <complex.h>
#include <pthread.h>
#include "../include/fractal_functions.h"
#include "../include/range_to_list.h"
#include "../include/color_functions.h"
#include "../include/usage.h"
#include "../include/parallel_escape.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

int main(int argc, char **argv)
{
	// F fractal, Q quality, P power, M max iteration, C center, R range, J conjugate, H help
	char *options = "F:Q:P:M:C:R:HhJ";
	usage intput; // struct holds user options
	char check = prase(argc, argv, options, &intput);
	if (check != '0') {
		check_func(check);
		return 1;
	}

	printf("this is the good good fractal creation software made by ghamdi lmt\n");
	
	// image and fractal values from usage struct
	int hight = intput.h;
	int width = intput.w;
	char fractal = intput.f;
	int power = intput.p;
	int maxlooplength = intput.m;
	double xcenter = intput.xc;  
	double ycenter = intput.yc;
	double range = intput.r;
	int conjugate = intput.conj;

	const int all_points = width * hight;

	// Declaration of function pointer variable (thanks gpt)
	int(*fractal_function)(double complex c, int n, int maxlength);
	// chosing fractal function
	if (fractal == 'M' && conjugate) {
		fractal_function = conj_mandel_fractal;
	} else if (fractal == 'M') {
		fractal_function = mandel_fractal;
	} else if (fractal == 'B' && conjugate) {
		fractal_function = conj_ship_fractal;
	} else if (fractal == 'B') {
		fractal_function = ship_fractal;
	}

	// image ratio normalised x and y complex plane value sets
	double xset_range = range * ((double)width / (double)hight);
	double yset_range = range;
	double x[width];
	double y[hight];
	centered_rangelist(x, xcenter, xset_range, width);
	centered_rangelist(y, ycenter, yset_range, hight);

	// complex points array
	double complex *complex_ary = calloc(all_points, sizeof(double complex));	
	// escape array holds the number of itertions for complex point to escape
	int *escape_ary = calloc(all_points, sizeof(int));
	if (escape_ary == NULL || complex_ary == NULL) {
		printf("not enough space in memory");
		return 4;
	}

	// set all complex points
	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < width; j++)
		{
			complex_ary[i*width + j] = x[j] + I*y[i];
		}
	}

	// getting parallelized
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	para_args t1args;
	para_args t2args;
	para_args t3args;
	para_args t4args;

	base_para_args bpa;
	bpa.comp = complex_ary;
	bpa.escape = escape_ary;
	bpa.frct = fractal_function;
	bpa.max = maxlooplength;
	bpa.n = power;

	int tasks_num = 10; // the number of tasks
	work tasks[tasks_num];
	
	int task_size = (int)roundf(all_points / tasks_num);
	for (int i = 0; i < tasks_num; i++)
	{
		tasks[i].pi = i * task_size;
		tasks[i].pf = (i+1) * task_size;
	}
	
	int tasks_track = 0;
	while (tasks_track < tasks_num)
	{	
		if (tasks_track < tasks_num) {
			t1args = arg_write(bpa, tasks[tasks_track]);
			tasks_track++;
			pthread_create(&thread1, NULL, para_escape, (void*)&t1args);
		}
		if (tasks_track < tasks_num) {
			t2args = arg_write(bpa, tasks[tasks_track]);
			tasks_track++;
			pthread_create(&thread2, NULL, para_escape, (void*)&t2args);
		}
		if (tasks_track < tasks_num) {
			t3args = arg_write(bpa, tasks[tasks_track]);
			tasks_track++;
			pthread_create(&thread3, NULL, para_escape, (void*)&t3args);
		}
		if (tasks_track < tasks_num) {
			t4args = arg_write(bpa, tasks[tasks_track]);
			tasks_track++;
			pthread_create(&thread4, NULL, para_escape, (void*)&t4args);
		}

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		pthread_join(thread3, NULL);
		pthread_join(thread4, NULL);
	}
	
	free(complex_ary);

	// grayscale image data array writen by color function
	uint8_t *stb_ary = norm_escape_stb(hight, width, escape_ary);
	// black and white image data array writen by color function
	uint8_t *stb_mono_ary = escape_stb_mono(hight, width, escape_ary);
	if (stb_mono_ary == NULL || stb_ary == NULL) {
		printf("not enough space in memory");
		return 6;
	}

	// writing the images via the stb image library(stb_image_write.h)
	stbi_write_bmp("frct_stb.bmp", width, hight, 3, stb_ary);
	// stbi_write_bmp("frct_mono_stb.bmp", width, hight, 1, stb_mono_ary); // not different enough to save
	stbi_write_png("frct_stb.png", width, hight, 3, stb_ary, sizeof(uint8_t) * 3 * width);
	stbi_write_png("frct_mono_stb.png", width, hight, 1, stb_mono_ary, sizeof(uint8_t) * width);

	free(stb_mono_ary);
	free(stb_ary);
	free(escape_ary);

	return 0;
}
