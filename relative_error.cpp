#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "relative_error.h"

using namespace std;

/*
 * This is the algorithm for solving the tridiagonal matrix in a) and b)
 *
 */

double f(double x) // Function f(x)
{
    return 100 * exp(-10 * x);
}

double solution(double x) // Solution u(x)
{
    return 1 - (1 - exp(-10)) * x - exp(-10 * x);
}

// Finds the maximum value in an array x with the length n
double max(double x[], int n)
{
    double max_value = -10e10;
    for(int i = 1; i < n + 1; i++)
    {
        if(x[i] > max_value)
        {
            max_value = x[i];
        }
    }
    return max_value;
}

// Calculates maximum error using u(x) and v(x) with length n
double max_relative_error(double u[], double v[], int n)
{
    double *relative_error = new double[n+2];

    for(int i = 1; i < n + 1; i++)
    {
        relative_error[i] = log10(abs((v[i] - u[i])/u[i]));
    }
    return max(relative_error, n);
}

void relative_error(int n)
{
    // Initial constants
    double h = 1.0/(n + 1.0);
    double *x = new double[n+2];
    double *b_tilde = new double[n+1];

    // Declare variables of matrix A
    int *a = new int[n+1];
    int *b = new int[n+1];
    int *c = new int[n+1];

    // Real and approximated solution
    double *u = new double[n+2]; // Analytical solution
    double *v = new double[n+2]; // Numerical solution

    // Initializing first points (they are not indexed later)
    u[0] = 0;
    v[0] = 0;

    // Initializing x
    for(int i = 0; i < n + 2; i++)
    {
        x[i] = i * h;
        // cout << "x = " << x[i] << " and b~ = h^2f(x) = " << h * h * f(x[i]) << endl;
    }

    // Initializing b_tilde, u, a, b and c
    for(int i = 1; i < n + 1; i++)
    {
        // b_tilde = h^2 * f_i
        b_tilde[i] = h * h * f(x[i]);
        // cout << "b_tilde = " << b_tilde[i] << "\tfor x = " << x[i] << endl;

        u[i] = solution(x[i]);
        cout << "u = " << u[i] << "\tfor x = " << x[i] << endl;

        a[i] = -1;
        b[i] = 2;
        c[i] = -1;
    }
    a[1] = 0;
    c[n] = 0;

    /* Algorithm for finding v:
     * a(i) * v(i-1) + b(i) * v(i) + c(i) * v(i+1) = b_tilde(i)
     *
     * Forward substitution:
     * b_temp(i) = b(i) - (c(i-1) * a(i-1)) / b_temp(i-1)
     */

    // Declare temporary variabel for Gaussian elimination
    double *diagonal_temp = new double[n+1];
    double b_temp = b[1];
    v[1] = b_tilde[1] / b_temp; // v(1) = b_tilde(1) / b_temp(1)

    cout << "\nForward substitution:" << endl;
    for(int i = 2; i < n + 1; i++)
    {
        // Temporary value needed in next loop
        diagonal_temp[i] = c[i-1] / b_temp;

        // Temporary diagonal element
        b_temp = b[i] - a[i] * diagonal_temp[i];

        // Updating right hand side of matrix equation
        v[i] = (b_tilde[i] - v[i-1] * a[i]) / b_temp;
    }

    // Backward substitution, in general: v(i) = (b_tilde(i) - c(i) * v(i+1)) / b_temp(i)
    for(int i = n; i > 0; i--)
    {
        v[i] -= diagonal_temp[i+1] * v[i+1];
    }

    double max_error = max_relative_error(u, v, n);
    cout << "\nMax error for N = " << n << ": " << max_error << endl;

    // Deletes arrays after use to free space
    delete [] x;
    delete [] b_tilde;
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] u;
    delete [] v;
}
