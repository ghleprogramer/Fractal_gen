#include <complex.h>
#include "../include/parallel_escape.h"
#include "../include/fractal_functions.h"
#include "../include/usage.h"
#include "../include/main.h"

void *para_escape(void *in_args)
{
	para_args args = *(para_args*)in_args;

	for (int i = args.pi; i < args.pf; i++) {
		escape_ary[i] = fractal_function(complex_ary[i], power, maxlooplength);
	}
	args.done[args.thread_n] = thread_available;
	return (void*) 0;
}

para_args arg_write(domain p, int *done, int t_n)
{
	para_args arg;
	arg.pf = p.pf;
	arg.pi = p.pi;
	arg.thread_n = t_n;
	arg.done = done;

	return arg;
}
