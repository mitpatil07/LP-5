#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int main()
{
    int n;

    // Input size of array
    cout << "Enter size of array: ";
    cin >> n;

    // Arrays for sequential and parallel sorting
    vector<int> seq(n), par(n);

    // Input array elements
    cout << "\nEnter array elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> seq[i];

        // Copy same values into both arrays
        par[i] = seq[i];
    }

    cout << "\nOriginal Array:\n";

    for (int i = 0; i < n; i++)
    {
        cout << seq[i] << " ";
    }

    cout << "\n\n";

    /*
    ==================================================
            SEQUENTIAL BUBBLE SORT
    ==================================================
    */

    // Start timer
    double start =
        (double)clock() / CLOCKS_PER_SEC;

    // Sequential Bubble Sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // Swap adjacent elements
            if (seq[j] > seq[j + 1])
            {
                swap(seq[j], seq[j + 1]);
            }
        }
    }

    // End timer
    double end =
        (double)clock() / CLOCKS_PER_SEC;

    // Print sequential execution time
    cout << "Sequential Bubble Sort Time: "
         << end - start << " seconds\n";

    // Print sequential sorted array
    cout << "\nSequential Sorted Array:\n";

    for (int i = 0; i < n; i++)
    {
        cout << seq[i] << " ";
    }

    cout << "\n\n";

    /*
    ==================================================
            PARALLEL BUBBLE SORT
    ==================================================

    Odd-Even Transposition logic
    */

    // Start timer
    start =
        (double)clock() / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++)
    {
        // EVEN PHASE
        if (i % 2 == 0)
        {
            for (int j = 0; j < n - 1; j += 2)
            {
                if (par[j] > par[j + 1])
                {
                    swap(par[j], par[j + 1]);
                }
            }
        }

        // ODD PHASE
        else
        {
            for (int j = 1; j < n - 1; j += 2)
            {
                if (par[j] > par[j + 1])
                {
                    swap(par[j], par[j + 1]);
                }
            }
        }
    }

    // End timer
    end =
        (double)clock() / CLOCKS_PER_SEC;

    // Print parallel execution time
    cout << "Parallel Bubble Sort Time: "
         << end - start << " seconds\n";

    // Print parallel sorted array
    cout << "\nParallel Sorted Array:\n";

    for (int i = 0; i < n; i++)
    {
        cout << par[i] << " ";
    }

    cout << endl;

    return 0;
}

/*

==================================================
            COMPILATION COMMAND
==================================================

g++ Bubble_sort.cpp -o Bubble_sort

==================================================
                RUN COMMAND
==================================================

./Bubble_sort.exe

==================================================
                SAMPLE INPUT
==================================================

Enter size of array: 5

Enter array elements:
5 2 9 1 7

==================================================
                SAMPLE OUTPUT
==================================================

Original Array:
5 2 9 1 7

Sequential Bubble Sort Time: 0.00001 seconds

Sequential Sorted Array:
1 2 5 7 9

Parallel Bubble Sort Time: 0.00001 seconds

Parallel Sorted Array:
1 2 5 7 9

==================================================

*/