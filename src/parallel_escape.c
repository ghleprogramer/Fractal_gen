#include <complex.h>
#include "../include/parallel_escape.h"
#include "../include/fractal_functions.h"

void *para_escape(void *in_args)
{
	para_args args = *(para_args*)in_args;

	for (int i = args.pi; i < args.pf; i++)
	{
		args.escape[i] = args.frct(args.comp[i], args.n, args.max);
	}
}

para_args arg_write(base_para_args bpa, work p)
{
	para_args arg;
	arg.escape = bpa.escape;
	arg.comp = bpa.comp;
	arg.frct = bpa.frct;
	arg.max = bpa.max;
	arg.n = bpa.n;
	arg.pf = p.pf;
	arg.pi = p.pi;

	return arg;
}
