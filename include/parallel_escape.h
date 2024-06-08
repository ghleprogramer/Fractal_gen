#ifndef PARALLEL_ESCAPE_H_
#define PARALLEL_ESCAPE_H_

#include <complex.h>

struct para_args
{
	int *escape;
	double complex *comp;
	int (*frct)(double complex, int, int);
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
	int (*frct)(double complex, int, int);
	int n;
	int max;
};
typedef struct base_para_args base_para_args;

struct domain
{
	int pi;
	int pf;
};
typedef struct domain domain;

void *para_escape(void *args);

para_args arg_write(base_para_args bpa, domain p);

#endif
