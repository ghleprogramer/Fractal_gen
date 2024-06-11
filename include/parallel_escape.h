#ifndef PARALLEL_ESCAPE_H_
#define PARALLEL_ESCAPE_H_

#include <complex.h>

struct para_args
{
	int pi;
	int pf;
	int thread_n;
	int *done;
};
typedef struct para_args para_args;

struct domain
{
	int pi;
	int pf;
};
typedef struct domain domain;

void *para_escape(void *args);

para_args arg_write(domain p, int *done, int t_n);

#define thread_available 1
#define thread_not_available 0

#endif
