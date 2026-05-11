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