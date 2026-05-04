#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V + 1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /* -------- DFS UTILITY -------- */
    void dfsUtil(int node, vector<bool>& visited) {

        bool process = false;

        #pragma omp critical
        {
            if (!visited[node]) {
                visited[node] = true;
                process = true;
                cout << node << " ";
            }
        }

        if (!process) return;

        for (int neighbor : adj[node]) {
            #pragma omp task
            dfsUtil(neighbor, visited);
        }
    }

    /* -------- PARALLEL DFS -------- */
    void parallelDFS(int start) {
        vector<bool> visited(V + 1, false);

        cout << "\nParallel DFS Traversal: ";

        #pragma omp parallel
        {
            #pragma omp single
            dfsUtil(start, visited);
        }

        cout << endl;
    }
};

int main() {
    int V, E;

    cout << "Enter vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter edges: ";
    cin >> E;

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Start node: ";
    cin >> start;

    omp_set_num_threads(4);

    double start_time = omp_get_wtime();
    g.parallelDFS(start);
    double end_time = omp_get_wtime();

    cout << "Time: " << end_time - start_time << " sec\n";

    return 0;
}
