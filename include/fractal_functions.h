#ifndef FRACTAL_FUNCTION_H_
#define FRACTAL_FUNCTION_H_

double complex seed;
int(*fractal_function)(double complex c, int n, int maxlength);

int julia_fractal(double complex c, int n, int maxlength);
int mandel_fractal(double complex c, int n, int maxlength);
int conj_mandel_fractal(double complex c, int n, int maxlength);
int ship_fractal(double complex c, int n, int maxlength);

void set_fractal(void);

#endif
