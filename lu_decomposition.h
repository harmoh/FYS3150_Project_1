#ifndef LU_DECOMPOSITION_H
#define LU_DECOMPOSITION_H

double f_lu(double x);
double solution_lu(double x);
double max_lu(double x[], int n);
double max_relative_error_lu(double u[], double v[], int n);
double lu_decomposition(char *outfilename, int exponent);

#endif // LU_DECOMPOSITION_H
