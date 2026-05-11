#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Graph adjacency list
vector<vector<int>> graph;

// Visited array
vector<int> visited;

/*
    Parallel DFS Function
*/
void dfs(int node)
{
    // Mark node as visited
    visited[node] = 1;

    // Print current node
    cout << node << " ";

    // Traverse all adjacent nodes in parallel
    #pragma omp parallel for
    for (int i = 0; i < graph[node].size(); i++)
    {
        int next = graph[node][i];

        // Check if node is not visited
        if (!visited[next])
        {
            // Create parallel task
            #pragma omp task
            {
                if (!visited[next])
                {
                    dfs(next);
                }
            }
        }
    }
}

int main()
{
    int n, e;

    // Input number of vertices
    cout << "Enter number of vertices: ";
    cin >> n;

    // Input number of edges
    cout << "Enter number of edges: ";
    cin >> e;

    // Resize graph and visited array
    graph.resize(n);
    visited.resize(n, 0);

    cout << "\nEnter edges one by one (u v):\n";

    // Input edges
    for (int i = 0; i < e; i++)
    {
        int u, v;

        cout << "Enter edge " << i + 1 << ": ";
        cin >> u >> v;

        // Add edge for undirected graph
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "\nParallel DFS Traversal starting from node 0:\n";

    // Start DFS from node 0
    dfs(0);

    cout << endl;

    return 0;
}

/*

========================
COMPILATION COMMAND
========================

g++ -fopenmp DFS.cpp -o main

========================
RUN COMMAND
========================

./main.exe

========================
SAMPLE INPUT
========================

Enter number of vertices: 5
Enter number of edges: 4

Enter edges one by one (u v):

Enter edge 1: 0 1
Enter edge 2: 0 2
Enter edge 3: 1 3
Enter edge 4: 1 4

========================
OUTPUT
========================

Parallel DFS Traversal starting from node 0:
0 1 3 4 2

*/