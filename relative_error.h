#ifndef RELATIVE_ERROR_H
#define RELATIVE_ERROR_H

double f_error(double x);
double solution_error(double x);
double max(double x, int n);
double max_relative_error(double u[], double v[], int n);
double relative_error(int n);

#endif // RELATIVE_ERROR_H
