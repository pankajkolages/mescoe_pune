#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

const int MAXN = 100000;

vector<int> adj[MAXN + 5];
bool visited[MAXN + 5];

// Parallel DFS Function
void dfs(int node) {
    // Mark visited safely
    #pragma omp critical
    {
        if (visited[node]) return;
        visited[node] = true;
        cout << node << " ";
    }

    // Explore neighbors in parallel
    #pragma omp parallel for
    for (int i = 0; i < adj[node].size(); i++) {
        int next_node = adj[node][i];

        if (!visited[next_node]) {
            dfs(next_node);
        }
    }
}

int main() {
    int n, m;

    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    // Input edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    int start_node;
    cout << "Enter starting node: ";
    cin >> start_node;

    // Initialize visited array
    for (int i = 1; i <= n; i++) {
        visited[i] = false;
    }

    cout << "DFS Traversal: ";

    // Start parallel region
    #pragma omp parallel
    {
        #pragma omp single
        {
            dfs(start_node);
        }
    }

    cout << endl;

    return 0;
}