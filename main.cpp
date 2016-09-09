#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

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
        outfilename = argv[1];
        n = atoi(argv[2]);
    }

    double x = 10;
    cout << "f(" << x << ") = " << f(x) << endl;
    cout << "solution(" << x << ") = " << solution(x) << endl;

    return 0;
}
