// file holds all usage related functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include "../include/usage.h"

#define fractal_case 'F'
#define quality_case 'Q'
#define range_case 'R'
#define center_case 'C'
#define power_case 'P'
#define max_iter_case 'M'
#define conjugate_case 'J'

#define help_case 'H'
#define help_case_2 'h'
char* helptxt = "usage: ./fractal_gen <option-s>\noptions:\n-F M(mandelbrot) B(burningship) fractal type\n\
-P pos num fractal equation power\n-R pos num range of fractal\n-C num,num farctal center\n\
-M pos num fractal equation max number of iterations\n-J nosubopt conjugate fractal equation(neg power)\n\
-Q SD ED HD 4K 8K image quality\n";

char prase(int argc, char **argv, char *options, usage *usage)
{
	// default values
	usage->f = 'M';
	usage->h = 1080;
	usage->w = 1920;
	usage->p = 2;
	usage->xc  = -0.6;
	usage->yc = 0;
	usage->r = 4;
	usage->m = 100;
	usage->conj = 0;

	// no options, use defaults
	char check = '0';
	if (argc == 1) {
		return check;
	}

	// prasing all given options from the getopt function
	int opt;
	while ((opt = getopt(argc, argv, options)) != -1)
	{
		check = prase_switch(opt, usage);
		if (check != '0') {
			return check;
		}
	}
	return check;
}

char prase_switch(int opt, usage *usage)
{
	char check = '0'; // succes
	// option switch
	// the father of all switchs to be switched
	switch (opt)
	{
	case fractal_case: {
		// check valid fractal
		if (!strstr(" m M B b", optarg) || strlen(optarg) > 2) {
			return fractal_case;
		}
		// procces option
		// if option arg starts with space " arg"
		int optarg_indx = 0;
		if (isblank(optarg[0]))
			optarg_indx = 1;
		usage->f = toupper(optarg[optarg_indx]);
		break;
	}

	case power_case: {
		usage->p = (int)strtol(optarg, NULL, 10);
		// valid power check
		if (usage->p < 1)
			return power_case;
		// massage in case too high of a power by mistake
		// though the program can handel it just fine
		if (usage->p > 9) {
			printf("fractal function power has been set to %i if it is a mistake the program can be terminated by ctrl+c\n", usage->p);
		}
		break;
	}

	case range_case: {
		usage->r = strtod(optarg, NULL);
		// valid range check
		if (usage->r < 1)
			return range_case;
		break;
	}

	case center_case: {
		// x, y from optarg as strings
		char *x = NULL;
		char *y = NULL;
		x = strtok(optarg, ",");
		y = strtok(NULL, ",");
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
		usage->xc = strtod(x, check_ptr);
		if (usage->xc == 0 && !strcmp(*check_ptr, y))
			return center_case;
		
		usage->yc = strtod(y, check_ptr);
		if (usage->yc == 0 && !strcmp(*check_ptr, y))
			return center_case;

		free(check_ptr);
		break;
	}

	case max_iter_case: {
		usage->m = strtod(optarg, NULL);
		// valid max iterations check
		if (usage->m < 1)
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
			usage->h = 480;
			usage->w = 720;
			break;

		case 'E'+'D':
			usage->h = 720;
			usage->w = 1280;
			break;
		
		case 'H'+'D':
			usage->h = 1080;
			usage->w = 1920;
			break;

		case '4'+'K':
			usage->h = 2160;
			usage->w = 3840;
			break;

		case '8'+'K':
			usage->h = 4320;
			usage->w = 7680;
			break;

		default:
			return quality_case;
			break;
		}
		break;
	}

	case conjugate_case:
		// set conj if option used
		usage->conj = 1;
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
	
	case power_case:
		printf("invaled power -P pos num\n");
		break;

	case range_case:
		printf("invaled range -R pos num\n");
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
