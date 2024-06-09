#include <complex.h>
#include "../include/parallel_escape.h"
#include "../include/fractal_functions.h"

void *para_escape(void *in_args)
{
	para_args args = *(para_args*)in_args;

	for (int i = args.pi; i < args.pf; i++) {
		args.escape[i] = args.frct(args.comp[i], args.pow, args.max);
	}
	args.done[args.thread_n] = thread_available;
	return (void*) 0;
}

para_args arg_write(base_para_args bpa, domain p, int *done, int t_n)
{
	para_args arg;
	arg.escape = bpa.escape;
	arg.comp = bpa.comp;
	arg.frct = bpa.frct;
	arg.max = bpa.max;
	arg.pow = bpa.pow;
	arg.pf = p.pf;
	arg.pi = p.pi;
	arg.thread_n = t_n;
	arg.done = done;

	return arg;
}
