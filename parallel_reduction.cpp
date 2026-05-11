#include <iostream>
#include <omp.h>
using namespace std;

int main()
{

    int a[] = {1, 2, 3, 4, 5};

    int n = 5;

    int sum = 0;
    int min = a[0];
    int max = a[0];

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }

#pragma omp parallel for reduction(min : min)
    for (int i = 0; i < n; i++)
    {
        if (a[i] < min)
            min = a[i];
    }

#pragma omp parallel for reduction(max : max)
    for (int i = 0; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }

    double avg = (double)sum / n;

    cout << "Sum = " << sum << endl;
    cout << "Min = " << min << endl;
    cout << "Max = " << max << endl;
    cout << "Average = " << avg << endl;

    return 0;
}


/*

==================================================
            COMPILATION COMMAND
==================================================

g++ -fopenmp parallel_reduction.cpp -o reduction

==================================================
                RUN COMMAND
==================================================

./reduction.exe

==================================================
                SAMPLE OUTPUT
==================================================

Array Elements:
1 2 3 4 5

Sum = 15
Minimum = 1
Maximum = 5
Average = 3

==================================================

*/