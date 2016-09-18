#ifndef TRIDIAGONAL_H
#define TRIDIAGONAL_H

double f(double x);
double solution(double x);
double max(double x[], int n);
double max_relative_error(double u[], double v[], int n);
double tridiagonal(char *outfilename, int base, int exponent);

#endif // TRIDIAGONAL_H
