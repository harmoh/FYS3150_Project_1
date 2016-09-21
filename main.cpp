#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <armadillo>
#include <string>
#include "tridiagonal.h"
#include "lu_decomposition.h"

using namespace arma;
using namespace std;

ofstream ofile_summary;

/*
 * This is the main program for Project 1 in FYS3150.
 */

int main(int argc, char *argv[])
{
    // Declare initial variables
    char *outfilename;
    int base;
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
        outfilename = argv[1];      // First command line argument
        base = atoi(argv[2]);       // Second command line argument
        exponent = atoi(argv[3]);   // Third command line argument
    }

    // Open file and write to file
    string error_time = outfilename;
    error_time.append(to_string(exponent));
    error_time.append("_error_time");
    error_time.append(".txt");
    ofile_summary.open(error_time);
    ofile_summary << setiosflags(ios::showpoint | ios::uppercase);
    ofile_summary << "# N:" << setw(18) <<  "h:" << setw(24) <<
                     "Error:" << setw(16) <<  "Time [sec]:" <<
                     setw(28) << "Time (LU Decomp.) [sec]:" << endl;

    // Declare start and final time
    clock_t start, start_lu, finish, finish_lu;
    for(int i = 1; i < exponent + 1; i++)
    {
        int n = pow(base, i);
        double h = 1.0 / (n + 1.0);

        start = clock();
        double max_error = tridiagonal(outfilename, base, i);
        finish = clock();

        start_lu = clock();
        lu_decomposition(base, i);
        finish_lu = clock();

        double time_temp = (double) (finish - start)/(CLOCKS_PER_SEC);
        double time_temp_lu = (double) (finish_lu - start_lu)/(CLOCKS_PER_SEC);
        cout << "Max error for N = " << base << "e" << i << ": " << max_error <<
                " time used: " << time_temp << " sec and " << time_temp_lu <<
                " sec." << endl;

        ofile_summary << setw(0) << setprecision(8) << base << "e" << i;
        ofile_summary << setw(18) << setprecision(8) << h;
        ofile_summary << setw(18) << setprecision(8) << pow(10, max_error);
        ofile_summary << setw(24) << setprecision(8) << time_temp;
        ofile_summary << setw(24) << setprecision(8) << time_temp_lu << endl;
    }
    ofile_summary.close();

    return 0;
}
