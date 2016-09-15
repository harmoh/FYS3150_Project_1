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
    int exponent;

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
        exponent = atoi(argv[2]);      // Second command line argument
    }

    // Task a) and b)
    // Performs row reduction by forward and backward substitution and prints to file
    for(int i = 1; i < exponent + 1; i++)
    {
        row_reduction(outfilename, i);
    }

    return 0;
}
