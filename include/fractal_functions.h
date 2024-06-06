#ifndef FRACTAL_FUNCTION_H_
#define FRACTAL_FUNCTION_H_

int mandel_fractal(double complex c, int n, int maxlength);
int conj_mandel_fractal(double complex c, int n, int maxlength);
int ship_fractal(double complex c, int n, int maxlength);
int conj_ship_fractal(double complex c, int n, int maxlength);

#endif
