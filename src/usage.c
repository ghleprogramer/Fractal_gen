// file holds all usage related functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <complex.h>
#include "../include/fractal_functions.h"
#include "../include/usage.h"
#include "../include/main.h"

#define fractal_case 'F'
int fractal_called = 0;
#define julia_case 'J'
#define quality_case 'Q'
#define range_case 'R'
#define center_case 'C'
#define power_case 'P'
#define max_iter_case 'M'
#define threads_case 'T'
#define conjugate_case 'G'

#define help_case 'H'
#define help_case_2 'h'
char* helptxt = "usage: ./fractal_gen <option-s>\noptions:\n-F M(mandelbrot) B(burningship) fractal type\n\
-P pos num fractal equation power\n-R pos num range of fractal\n-C num,num farctal center\n\
-M pos num fractal equation max number of iterations\n-J nosubopt conjugate fractal equation(neg power)\n\
-Q SD ED HD 4K 8K image quality\n";

char prase(int argc, char **argv, char *options)
{
	// default values
	fractal = 'M';
	hight = 1080;
	width = 1920;
	power = 2;
	xcenter  = -0.6;
	ycenter = 0;
	range = 4;
	maxlooplength = 100;
	thread_count = 1;
	conjugate = 0;
	seed = 0.4 + I*0.4;

	// no options, use defaults
	char check = '0';
	if (argc == 1) {
		return check;
	}

	// prasing all given options from the getopt function
	int opt;
	while ((opt = getopt(argc, argv, options)) != -1)
	{
		check = prase_switch(opt);
		if (check != '0') {
			return check;
		}
	}
	return check;
}

char prase_switch(int opt)
{
	char check = '0'; // succes
	// option switch
	// the father of all switchs to be switched
	switch (opt)
	{
	case fractal_case: {
		fractal_called = 1;
		if (fractal == 'J') {
			printf("-J opt sets fractal type to quad julia by default -F and -J should not be called togather\n");
			return 1;
		}
		// check no opt
		if (strlen(optarg) > 2) {
			return fractal_case;
		}
		// check valid opt
		if (strchr("mMBb", optarg[0]) == NULL
			&& strchr("mMBb", optarg[1]) == NULL) {
			return fractal_case;
		}
		// first is blank
		int optarg_indx = 0;
		if (isblank(optarg[0])) {
			optarg_indx = 1;
		}

		fractal = toupper(optarg[optarg_indx]);

		if (fractal == 'B' && conjugate) {
			printf("only the mandelbrot faractal has an implemented conjugate function");
			return 1;
		}
		break;
	}

	case julia_case: {
		if (fractal_called) {
			printf("-J opt sets fractal type to quad julia by default -F and -J should not be called togather\n");
			return julia_case;
		}
		if (conjugate) {
			printf("only the mandelbrot faractal has an implemented conjugate function");
			return 1;
		}

		// set to julia
		fractal = 'J';
		// seed values as num,num
		char *real_chr = NULL;
		char *imag_chr = NULL;
		real_chr = strtok(optarg, ",");
		imag_chr = strtok(NULL, " ");
		// invalid format
		if (strtok(NULL, ",") != NULL || real_chr == NULL || imag_chr == NULL) {
			return julia_case;
		}
		// big enough check pointer
		char **check_ptr = malloc(strlen(real_chr) + strlen(imag_chr));

		double real = strtod(real_chr, check_ptr);
		// strtod check
		if (real == 0 && !strcmp(*check_ptr, imag_chr)) {
			return julia_case;
		}
		
		double imag = strtod(imag_chr, check_ptr);
		// strtod check
		if (imag == 0 && !strcmp(*check_ptr, imag_chr)) {
			return julia_case;
		}

		free(check_ptr);
		seed = real + I*imag;
		break;

	}

	case power_case: {
		power = (int)strtol(optarg, NULL, 10);
		// valid power check
		if (power < 1)
			return power_case;
		// massage in case too high of a power by mistake
		// though the program can handel it just fine
		if (power > 9) {
			printf("fractal function power has been set to %i if it is a mistake the program can be terminated by ctrl+c\n", power);
		}
		break;
	}

	case range_case: {
		range = strtod(optarg, NULL);
		// valid range check
		if (range <= 0)
			return range_case;
		break;
	}

	case center_case: {
		// x, y from optarg as strings
		char *x = NULL;
		char *y = NULL;
		x = strtok(optarg, ",");
		y = strtok(NULL, " ");
		// when too many optargs or token error
		if (strtok(NULL, ",") != NULL || x == NULL || y == NULL) {
			return center_case;
		}

		// check ptr that is big enough
		char **check_ptr = malloc(strlen(x) + strlen(y));
		// input check
		// harder validation is needed since zero is a valid center value
		// strtod return documentation from https://manual.cs50.io/3/strtod
		// If no conversion is performed, zero is returned and (unless endptr is null)
		// the value of nptr is stored in the location referenced by endptr.
		xcenter = strtod(x, check_ptr);
		if (xcenter == 0 && !strcmp(*check_ptr, y))
			return center_case;
		
		ycenter = strtod(y, check_ptr);
		if (ycenter == 0 && !strcmp(*check_ptr, y))
			return center_case;

		free(check_ptr);
		break;
	}

	case max_iter_case: {
		maxlooplength = strtod(optarg, NULL);
		// valid max iterations check
		if (maxlooplength < 1)
			return max_iter_case;
		break;
	}

	case quality_case: {
		int optarg_len = strlen(optarg);
		// valid quality check
		if (!strstr(" sd SD ed ED hd HD 4k 4K 8k 8K", optarg)
			|| optarg_len > 3 || optarg_len == 1)
			return quality_case;

		// option value proccesing 
		int optarg_val = 0;
		for (int i = 0; i < optarg_len; i++)
		{
			if(!isblank(optarg[i]))
				optarg_val += toupper(optarg[i]);
		}

		// switch to set the image quality values
		switch (optarg_val)
		{
		case 'S'+'D':
			hight = 480;
			width = 720;
			break;

		case 'E'+'D':
			hight = 720;
			width = 1280;
			break;
		
		case 'H'+'D':
			hight = 1080;
			width = 1920;
			break;

		case '4'+'K':
			hight = 2160;
			width = 3840;
			break;

		case '8'+'K':
			hight = 4320;
			width = 7680;
			break;

		default:
			return quality_case;
			break;
		}
		break;
	}

	case threads_case: {
		thread_count = strtod(optarg, NULL);
		// valid max iterations check
		if (thread_count < 1)
			return threads_case;
		// using more threads than a device has can cause undefined behavior
		// I think at it will least idk
		if (thread_count > 12) {
			printf("thread count has been set to %i if it is a mistake the program can be terminated by ctrl+c\n", thread_count);
		}
		break;
	}

	case conjugate_case:
		// set conj if option used
		if (fractal == 'B' || fractal == 'J') {
			printf("only the mandelbrot faractal has an implemented conjugate function(the tricorn fractal)");
			return 1;
		}
		conjugate = 1;
		break;

	case help_case:
		// case over flows
	case help_case_2:
		// two help cases since it is common to use -h not -H
		return help_case;
		break;

	case '?':
		return '1';
		break;

	default:
		break;
	}

	return check;
}

void check_func(char c)
{
	// check function takes in the check value and prints
	// the appropriate massage
	switch (c)
	{
	case '1':
		break;

	case fractal_case:
		printf("invaled fractal -F M, B\n");
		break;
	case julia_case:
		printf("invalid seed -J num,num\n");
		break;
	
	case power_case:
		printf("invaled power -P pos num\n");
		break;

	case range_case:
		printf("invaled range -R pos num\n");
		break;

	case threads_case:
		printf("invaled thread count -T pos num \n");
		break;

	case max_iter_case:
		printf("invaled number of iterations -M pos num\n");
		break;

	case center_case:
		printf("invaled center -C num,num\n");
		break;

	case quality_case:
		printf("invaled quality -Q ED, HD, 4K, 8K\n");
		break;

	case help_case:
		printf("%s", helptxt);
		break;

	default:
		break;
	}
	return;
}
