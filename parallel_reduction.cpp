#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

void perform_reduction(vector<int>& arr, int n) {
    int sum = 0;
    int min_val = INT_MAX;
    int max_val = INT_MIN;

    // Parallel reduction for Sum
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    // Parallel reduction for Minimum
    #pragma omp parallel for reduction(min : min_val)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
    }

    // Parallel reduction for Maximum
    #pragma omp parallel for reduction(max : max_val)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }

    double average = (double)sum / n;

    cout << "Sum: " << sum << endl;
    cout << "Min: " << min_val << endl;
    cout << "Max: " << max_val << endl;
    cout << "Average: " << average << endl;
}

int main() {
    int n;
    cout << "--- Parallel Reduction ---\n";
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    perform_reduction(arr, n);

    return 0;
}

/*
==================================================
            COMPILATION & RUN
==================================================
Compilation:
g++ -fopenmp parallel_reduction.cpp -o parallel_reduction

Run:
./parallel_reduction
==================================================
*/