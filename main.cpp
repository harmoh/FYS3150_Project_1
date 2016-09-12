#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <armadillo>

using namespace arma;
using namespace std;

ofstream ofile;

double f(double x) // Function f(x)
{
    return 100 * exp(-10 * x);
}

double solution(double x) // Solution u(x)
{
    return 1 - (1 - exp(-10)) * x - exp(-10 * x);
}

// Finds the minimal value in an array x with the length n
double min(double x[], int n)
{
    double min_value = 1;
    for(int i = 1; i < n + 1; i++)
    {
        if(x[i] < min_value)
        {
            min_value = x[i];
        }
    }
    return min_value;
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
        //cout << "Relative error for " << i << " = " << setprecision(16) << relative_error[i] << endl;
    }

    return max(relative_error, n);
}

int main(int argc, char *argv[])
{
    // Declare initial variables
    char *outfilename;
    int n;

    // Read from command line if there are enough arguments
    if(argc <= 2)
    {
        cout << "Bad usage: " << argv[0] <<
                "\nRead output file and n (int) on the same line." << endl;
        exit(1);
    }
    else
    {
        outfilename = argv[1];  // First command line argument
        n = atoi(argv[2]);      // Second command line argument
    }

    // Initial constants
    double h = 1.0/(n + 1.0);
    double *x = new double[n+2];
    double *b_tilde = new double[n+1];

    // Declare variables of matrix A
    int *a = new int[n+1];
    int *b = new int[n+1];
    int *c = new int[n+1];

    // Declare temporary variabel for Gaussian elimination
    double *diagonal_temp = new double[n+1];

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

    // Initializing b_tilde, a, b and c
    for(int i = 1; i < n + 2; i++)
    {
        // b_tilde = h^2 * f_i
        b_tilde[i] = h * h * f(x[i]);
        // cout << "b_tilde = " << b_tilde[i] << "\tfor x = " << x[i] << endl;

        u[i] = solution(x[i]);
        //cout << "u = " << u[i] << "\tfor x = " << x[i] << endl;

        a[i] = -1;
        b[i] = 2;
        c[i] = -1;
    }
    a[1] = 0;
    c[n] = 0;

    // Algorithm for finding v:
    // a(i) * v(i-1) + b(i) * v(i) + c(i) * v(i+1) = b_tilde(i)
    // Row reduction, forward substitution:
    double b_temp = b[1];
    v[1] = b_tilde[1] / b_temp;

    for(int i = 2; i < n + 1; i++)
    {
        // Temporary value needed in next loop
        diagonal_temp[i] = c[i-1] / b_temp;

        // Temporary diagonal element
        b_temp = b[i] - a[i] * diagonal_temp[i];

        // Updating right hand side of matrix equation
        v[i] = (b_tilde[i] - v[i-1] * a[i]) / b_temp;
        // cout << "v = " << v[i] << "\tfor x = " << x[i] << endl;

    }

    // Row reduction, backward substitution
    for(int i = n - 1; i > 0; i--)
    {
        v[i] -= diagonal_temp[i+1] * v[i+1];
        // cout << "v = " << v[i] << "\tfor x = " << x[i] << endl;
    }

    // Open file and write to file
    ofile.open(outfilename);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "# x:" << setw(15) <<  "u(x):" << setw(15) << "v(x):" << endl;
    for(int i = 1; i < n + 1; i++)
    {
        ofile << setw(0) << setprecision(8) << x[i];
        ofile << setw(15) << setprecision(8) << u[i];
        ofile << setw(15) << setprecision(8) << v[i] << endl;
    }
    ofile.close();

//    double *relative_error = new double[n+2];

//    for(int i = 1; i < n + 1; i++)
//    {
//        relative_error[i] = log10(abs((v[i] - u[i])/u[i]));
//        //cout << "Relative error for " << i << " = " << setprecision(16) << relative_error[i] << endl;
//    }

    //double max_error = max_relative_error(u, v, n);
    //cout << "Max error: " << setprecision(8) << max_error << endl;

    for(int i = 1; i < 4; i++)
    {
        int N = pow(10,i);
        double max_error = max_relative_error(u, v, N);
        cout << "Max error for N = " << N << ": " << max_error << endl;
    }

    delete [] x;
    delete [] b_tilde;
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] u;
    delete [] v;

    return 0;
}
