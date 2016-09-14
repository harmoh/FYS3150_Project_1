#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <armadillo>
#include "row_reduction.h"

using namespace arma;
using namespace std;

/*
 * This is the main program for Project 1 in FYS3150.
 */

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

    // Task a) and b)
    // Performs row reduction by forward and backward substitution, prints to file and calculates max error
    row_reduction(outfilename, n);



    /*
     * Loop for calculating error for several matrix sizes
    for(int i = 1; i < 4; i++)
    {
        int N = pow(10,i);
        double max_error = max_relative_error(u, v, N);
        cout << "Max error for N = " << N << ": " << max_error << endl;
    }
    */

    return 0;
}
