dfs
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int start) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (visited[node])
            continue;

        visited[node] = true;
        cout << node << " ";

        // Push neighbors onto stack
        for (int i = 0; i < graph[node].size(); i++) {
            if (!visited[graph[node][i]])
                s.push(graph[node][i]);
        }
    }
}

// ─────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────
int main() {
    int n, m, start;

    cout << "Enter number of nodes, edges, and start node: ";
    cin >> n >> m >> start;

    cout << "Enter " << m << " edges (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);  // undirected graph
    }

    cout << "\nDFS Traversal: ";
    dfs(start);
    cout << endl;

    return 0;
}
----------------------------------------------------------------------------------------------------------
min
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

-----------------------------------------------------------------------------------------------
bubble sort
#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> a(n), b(n);

    // Input elements
    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    // -----------------------------
    // Sequential Bubble Sort
    // -----------------------------
    double start = omp_get_wtime();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (a[j] > a[j + 1]) {

                swap(a[j], a[j + 1]);
            }
        }
    }

    double end = omp_get_wtime();

    cout << "\nSequential Bubble Sort Time: "
         << end - start << " sec\n";

    cout << "Sorted Array:\n";

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    // -----------------------------
    // Parallel Bubble Sort
    // -----------------------------
    start = omp_get_wtime();

    for (int i = 0; i < n; i++) {

        // Even Phase
        if (i % 2 == 0) {

            #pragma omp parallel for
            for (int j = 0; j < n - 1; j += 2) {

                if (b[j] > b[j + 1]) {

                    swap(b[j], b[j + 1]);
                }
            }
        }

        // Odd Phase
        else {

            #pragma omp parallel for
            for (int j = 1; j < n - 1; j += 2) {

                if (b[j] > b[j + 1]) {

                    swap(b[j], b[j + 1]);
                }
            }
        }
    }

    end = omp_get_wtime();

    cout << "\n\nParallel Bubble Sort Time: "
         << end - start << " sec\n";

    cout << "Sorted Array:\n";

    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }

    return 0;
}
---------------------------------------------------  ---------------------------------------------------------

merge
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
------------------------------------------------------------------------------------------------

bfs
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, e;

    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n);

    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> visited(n, false);
    queue<int> q;

    int start = 0;

    visited[start] = true;
    q.push(start);

    cout << "Parallel BFS Traversal: ";

    while (!q.empty()) {
        int size = q.size();

        vector<int> currentLevel;

        for (int i = 0; i < size; i++) {
            int node = q.front();
            q.pop();

            currentLevel.push_back(node);

            cout << node << " ";
        }

        #pragma omp parallel for
        for (int i = 0; i < currentLevel.size(); i++) {
            int node = currentLevel[i];

            for (int neighbor : graph[node]) {

                if (!visited[neighbor]) {

                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
    }

    return 0;
}

//g++ -fopenmp bfs.cpp -o bfs

//./bfs