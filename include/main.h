#ifndef MAIN_H_
#define MAIN_H_

// global constanats
int hight;
int width;
char fractal;
int power;
int maxlooplength;
double xcenter;  
double ycenter;
double range;
int thread_count;
int conjugate;

#include <complex.h>
// holds the number of itertions for complex point to escape
int *escape_ary;
// holds complex points
double complex *complex_ary;

#endif
