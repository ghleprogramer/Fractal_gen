// in this file is the deffention of the fractal functions
// to write the functions many sources were vary helpful
// wikipedia.org for the mandelbrot and the burning ship equations 
// theory.org for the burning ship equation 
// the descrption of the youtube video https://www.youtube.com/watch?v=5londkjHVmU
// 	by "The Mathemagicians' Guild Commons" or @tmgcommons for the conjugate functions 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "../include/fractal_functions.h"
#include "../include/usage.h"
#include "../include/main.h"

#define mandelbrot_EscapeValue 2 // proven true
#define burningship_EscapeValue 60 // not proven but is a common good number to use

int mandel_fractal(double complex c, int n, int maxlength)
{
	double complex z = c;
	for (int i = 1; i < maxlength; i++)
	{
		if (cabs(z) > mandelbrot_EscapeValue)
		{
			return i;
		}
        z = cpow(z, n) + c;
	}
	return 0;
}

// another name is the tricorn fractal
int conj_mandel_fractal(double complex c, int n, int maxlength)
{    
	double complex z = c;
	for (int i = 1; i < maxlength; i++)
	{
		if (cabs(z) > mandelbrot_EscapeValue)
		{
			return i;
		}
        z = cpow(conj(z), n) + c;
	}
	return 0;
}


int ship_fractal(double complex c, int n, int maxlength)
{
	double complex z = c;
	for (int i = 1; i < maxlength; i++)
	{
		if (cabs(z) > burningship_EscapeValue)
		{
			return i;
		}
        z = cpow(fabs(creal(z)) + I*fabs(cimag(z)), n) + c;
	}
	return 0;    
}

int julia_fractal(double complex c, int n, int maxlength)
{
	double complex z = c;
	c = seed;
	for (int i = 1; i < maxlength; i++)
	{
		if (cabs(z) > mandelbrot_EscapeValue)
		{
			return i;
		}
        z = cpow(z, n) + c;
	}
	return 0;
}

void set_fractal(void)
{
	if (fractal == 'M' && conjugate) {
		fractal_function = conj_mandel_fractal;
	} else if (fractal == 'M') {
		fractal_function = mandel_fractal;
	} else if (fractal == 'B') {
		fractal_function = ship_fractal;
	} else if (fractal == 'J') {
		fractal_function = julia_fractal;
	}

}