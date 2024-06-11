// a program for creating fractal images
// cd build && make && cd .. && ./fractal_gen 

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
#include "../include/main.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

int main(int argc, char **argv)
{
	// F fractal, Q quality, P power, M max iteration,
	// C center, R range, T thread count, J conjugate, H help
	char *options = "F:Q:P:M:C:R:T:J:L:HhG";
	char check = prase(argc, argv, options);
	if (check != '0') {
		check_func(check);
		return 1;
	}

	printf("this is the good good fractal creation software made by ghamdi lmt\n");
	
	// sets the farctal_function variable
	set_fractal();

	// image ratio normalised x and y complex plane value sets
	double xset_range = range * ((double)width / (double)hight);
	double yset_range = range;
	double x[width];
	double y[hight];
	centered_rangelist(x, xcenter, xset_range, width);
	centered_rangelist(y, ycenter, yset_range, hight);

	const int all_points = width * hight;

	// init complex points array
	complex_ary = calloc(all_points, sizeof(double complex));	
	// init escape array
	escape_ary = calloc(all_points, sizeof(int));
	if (escape_ary == NULL || complex_ary == NULL) {
		printf("not enough space in memory");
		return 4;
	}

	// set all complex points
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			complex_ary[i*width + j] = x[j] + I*y[i];
		}
	}

	// parallel fractal calculation
	// init threads and there checks
	pthread_t threads[thread_count];
	int thread_check[thread_count];
	for (int i = 0; i < thread_count; i++) {
		thread_check[i] = thread_available;
	}
	// init tasks
	int tasks_count = 100; // more or less randomly chosen
	domain task_domain[tasks_count];
	para_args task_args[tasks_count];

	// init domain for all tasks
	int task_size = (int)roundf(all_points / tasks_count);
	for (int i = 0; i < tasks_count; i++) {
		task_domain[i].pi = i * task_size;
		task_domain[i].pf = (i+1) * task_size;
	}
	
	// calculation loop
	int task_indx = 0;
	int thread_indx = 0;
	while (task_indx < tasks_count) {
		// loop over threads
		if (thread_indx >= thread_count) {
			thread_indx = 0;
		}
		if (thread_check[thread_indx]) {
			// if thread is available
			thread_check[thread_indx] = thread_not_available;

			task_args[task_indx] = arg_write(task_domain[task_indx], thread_check, thread_indx);
			pthread_create(&threads[thread_indx], NULL, para_escape, (void *)&task_args[task_indx]);
			task_indx++;
		}
		thread_indx++;
	}
	// join all
	for (int i = 0; i < thread_count; i++) {
		pthread_join(threads[i], NULL);
	}
	free(complex_ary);

	// grayscale image data array writen by color function
	uint8_t *stb_ary = norm_escape_stb(hight, width, escape_ary);
	// black and white image data array writen by color function
	uint8_t *stb_mono_ary = escape_stb_mono(hight, width, escape_ary);
	if (stb_mono_ary == NULL || stb_ary == NULL) {
		printf("not enough space in memory");
		return 7;
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
