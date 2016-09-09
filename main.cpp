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

int main(int argc, char *argv[])
{
    // Declear initial variables
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
    double h = 1/(n + 1);
    double *x = new double[n+2];
    double *b_t = new double[n+1];

    // Declear variables of matrix A
    int *a = new int[n+1];
    int *b = new int[n+1];
    int *c = new int[n+1];

    cout << "n = " << n << endl;
    cout << "a[1] = " << a[1] << endl;

    // Print functions
//    double x = 10;
//    cout << "f(" << x << ") = " << f(x) << endl;
//    cout << "solution(" << x << ") = " << solution(x) << endl;

    return 0;
}
