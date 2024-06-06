#ifndef PARALLEL_ESCAPE_H_
#define PARALLEL_ESCAPE_H_

#include <complex.h>

struct para_args
{
	int *escape;
	double complex *comp;
	int (*frct)(complex, int, int);
	int n;
	int max;
	int pi;
	int pf;
};
typedef struct para_args para_args;

struct base_para_args
{
	int *escape;
	double complex *comp;
	int (*frct)(complex, int, int);
	int n;
	int max;
};
typedef struct base_para_args base_para_args;

struct work
{
	int pi;
	int pf;
};
typedef struct work work;

void *para_escape(void *args);

para_args arg_write(base_para_args bpa, work p);

#endif
