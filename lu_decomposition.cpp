#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <armadillo>
#include <string>
#include "lu_decomposition.h"

using namespace std;
using namespace arma;

ofstream ofile_lu;

/*
 * This is the algorithm for solving the tridiagonal matrix in d)
 * using LU Decomposition
 *
 */


double f_lu(double x) // Function f(x)
{
    return 100 * exp(-10 * x);
}

double solution_lu(double x) // Solution u(x)
{
    return 1 - (1 - exp(-10)) * x - exp(-10 * x);
}

// Finds the maximum value in an array x with the length n
double max_lu(vec x, int n)
{
    double max_value = -10e10; // Setting a very low initial value
    for(int i = 0; i < n; i++)
    {
        if(x(i) > max_value)
        {
            max_value = x(i);
        }
    }
    return max_value;
}

// Calculates maximum error using u(x) and v(x) with length n
double max_relative_error_lu(vec u, vec v, int n)
{
    //double *relative_error = new double[n+2];
    vec relative_error(n);

    for(int i = 0; i < n; i++)
    {
        relative_error(i) = log10(abs((v(i) - u(i))/u(i)));
    }
    return max_lu(relative_error, n);
}

void lu_decomposition(int base, int exponent)
{
    // Convert to n = 10e(exponent)
    int n = pow(base,exponent);

    // Initial constants
    double h = 1.0/(n + 1.0);
    vec x(n);
    vec b_tilde(n);

    // Real and approximated solution
    vec u(n);
    vec v(n);

    // Creating and initializing matrix A
    mat A = zeros(n,n);
    A(0,0) = 2;
    A(0,1) = -1;
    A(n-1,n-1) = 2;
    A(n-1,n-2) = -1;
    for(int i = 1; i < n-1; i++)
    {
        A(i,i) = 2;
        A(i,i+1) = -1;
        A(i,i-1) = -1;
    }

    // Initializing x, b_tilde and u
    for(int i = 0; i < n; i++)
    {
        x(i) = i * h + h;
        b_tilde(i) = h * h * f_lu(x(i));
        u(i) = solution_lu(x(i));
    }

    v = solve(A, b_tilde);

    // double max_error = max_relative_error_lu(u, v, n);
}
