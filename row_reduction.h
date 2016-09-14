#ifndef ROW_REDUCTION_H
#define ROW_REDUCTION_H

double f(double x);
double solution(double x);
double max(double x, int n);
double max_relative_error(double u[], double v[], int n);
void row_reduction(char *outfilename, int n);

#endif // ROW_REDUCTION_H
