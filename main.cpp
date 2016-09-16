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

    // Open file and write to file
    string error_time = outfilename;
    error_time.append(to_string(exponent));
    error_time.append("_error_time");
    error_time.append(".txt");
    ofile_summary.open(error_time);
    ofile_summary << setiosflags(ios::showpoint | ios::uppercase);
    ofile_summary << "# N:" << setw(18) <<  "Error:" << setw(24) <<
                     "Error (LU Decomp.):" << setw(16) <<  "Time [sec]:" <<
                     setw(28) << "Time (LU Decomp.) [sec]:" << endl;

    // Declare start and final time
    clock_t start, start_lu, finish, finish_lu;
    for(int i = 1; i < exponent + 1; i++)
    {
        start = clock();
        double max_error = tridiagonal(outfilename, i);
        finish = clock();

        start_lu = clock();
        double max_error_lu_decomp = lu_decomposition(outfilename, i);
        finish_lu = clock();

        double time_temp = (double) (finish - start)/(CLOCKS_PER_SEC);
        double time_temp_lu = (double) (finish_lu - start_lu)/(CLOCKS_PER_SEC);
        //cout << setiosflags(ios::showpoint | ios::uppercase);
        cout << "Max error for N = 10e" << i << ": " << max_error << " time used: " <<
                time_temp << " sec and " << time_temp_lu << " sec." << endl;

        ofile_summary << setw(0) << setprecision(8) << "10e" << i;
        ofile_summary << setw(18) << setprecision(8) << max_error;
        ofile_summary << setw(18) << setprecision(8) << max_error_lu_decomp;
        ofile_summary << setw(24) << setprecision(8) << time_temp;
        ofile_summary << setw(24) << setprecision(8) << time_temp_lu << endl;
    }
    ofile_summary.close();

    return 0;
}
