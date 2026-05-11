#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Merge Function
void merge(vector<int> &arr, int st, int mid, int end)
{
    vector<int> temp;

    int i = st;
    int j = mid + 1;

    // Compare elements from both halves
    while(i <= mid && j <= end)
    {
        if(arr[i] <= arr[j])
        {
            temp.push_back(arr[i]);
            i++;
        }
        else
        {
            temp.push_back(arr[j]);
            j++;
        }
    }

    // Remaining elements of left half
    while(i <= mid)
    {
        temp.push_back(arr[i]);
        i++;
    }

    // Remaining elements of right half
    while(j <= end)
    {
        temp.push_back(arr[j]);
        j++;
    }

    // Copy merged elements back
    for(int idx = 0; idx < temp.size(); idx++)
    {
        arr[st + idx] = temp[idx];
    }
}


// Sequential Merge Sort
void seqMergeSort(vector<int> &arr, int st, int end)
{
    // Base condition
    if(st >= end)
        return;

    int mid = (st + end) / 2;

    // Sort left half
    seqMergeSort(arr, st, mid);

    // Sort right half
    seqMergeSort(arr, mid + 1, end);

    // Merge sorted halves
    merge(arr, st, mid, end);
}


// Parallel Merge Sort
void parMergeSort(vector<int> &arr, int st, int end)
{
    // Base condition
    if(st >= end)
        return;

    int mid = (st + end) / 2;

    // Recursive calls
    parMergeSort(arr, st, mid);

    parMergeSort(arr, mid + 1, end);

    // Merge sorted halves
    merge(arr, st, mid, end);
}


int main()
{
    int n;

    // Input size of array
    cout << "Enter size of array: ";
    cin >> n;

    // Original array
    vector<int> a(n);

    // Input array elements
    cout << "Enter array elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // Copy array for parallel sort
    vector<int> b = a;

    double start, end;

    /*
    =========================================
        SEQUENTIAL MERGE SORT
    =========================================
    */

    start = (double)clock() / CLOCKS_PER_SEC;

    seqMergeSort(a, 0, a.size() - 1);

    end = (double)clock() / CLOCKS_PER_SEC;

    cout << "\nSequential Merge Sort Time: "
         << end - start << " sec\n";

    cout << "Sequential Sorted Array:\n";

    for(int x : a)
        cout << x << " ";

    cout << "\n\n";


    /*
    =========================================
        PARALLEL MERGE SORT
    =========================================
    */

    start = (double)clock() / CLOCKS_PER_SEC;

    parMergeSort(b, 0, b.size() - 1);

    end = (double)clock() / CLOCKS_PER_SEC;

    cout << "Parallel Merge Sort Time: "
         << end - start << " sec\n";

    cout << "Parallel Sorted Array:\n";

    for(int x : b)
        cout << x << " ";

    cout << endl;

    return 0;
}

/*

==================================================
            COMPILATION COMMAND
==================================================

g++ merge_sort.cpp -o merge

==================================================
                RUN COMMAND
==================================================

./merge.exe

==================================================
                SAMPLE INPUT
==================================================

Enter size of array: 5

Enter array elements:
5 2 9 1 7

==================================================
                SAMPLE OUTPUT
==================================================

Sequential Merge Sort Time: 0.00001 sec

Sequential Sorted Array:
1 2 5 7 9

Parallel Merge Sort Time: 0.00001 sec

Parallel Sorted Array:
1 2 5 7 9

==================================================

*/