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

	// parallelized
	int thread_num = 4;
	pthread_t threads[thread_num];

	base_para_args bpa;
	bpa.comp = complex_ary;
	bpa.escape = escape_ary;
	bpa.frct = fractal_function;
	bpa.max = maxlooplength;
	bpa.n = power;

	int tasks_num = 10;
	domain tasks[tasks_num];
	para_args task_args[tasks_num];
	
	int task_size = (int)roundf(all_points / tasks_num);
	// domain stuct set for all tasks
	for (int i = 0; i < tasks_num; i++)
	{
		tasks[i].pi = i * task_size;
		tasks[i].pf = (i+1) * task_size;
	}
	// parallel tasks args struct written
	for (int i = 0; i < tasks_num; i++)
	{
		task_args[i] = arg_write(bpa, tasks[i]);
	}
	
	int task_indx = 0;
	while (task_indx < tasks_num)
	{
		// run all threads on tasks from task indx
		for (int thread_indx = 0; thread_indx < thread_num; thread_indx++)
		{
			// check if tasks done
			if (!(task_indx < tasks_num)) {
				break;
			}
			pthread_create(&threads[thread_indx], NULL,
					para_escape, (void *)(&task_args[task_indx]));
			task_indx++;
		}
		// join all
		for (int thread_indx = 0; thread_indx < thread_num; thread_indx++)
		{
			pthread_join(threads[thread_indx], NULL);
		}
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
