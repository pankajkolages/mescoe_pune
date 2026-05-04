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

    /* -------- PARALLEL BFS -------- */
    void parallelBFS(int start) {
        vector<bool> visited(V + 1, false);
        vector<int> frontier, next_frontier;

        frontier.push_back(start);
        visited[start] = true;

        cout << "\nParallel BFS Traversal: ";

        while (!frontier.empty()) {
            next_frontier.clear();

            #pragma omp parallel
            {
                vector<int> local_next;

                #pragma omp for nowait
                for (int i = 0; i < frontier.size(); i++) {
                    int node = frontier[i];

                    #pragma omp critical
                    cout << node << " ";

                    for (int neighbor : adj[node]) {
                        bool add = false;

                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                add = true;
                            }
                        }

                        if (add) {
                            local_next.push_back(neighbor);
                        }
                    }
                }

                #pragma omp critical
                next_frontier.insert(next_frontier.end(),
                                     local_next.begin(),
                                     local_next.end());
            }

            frontier = next_frontier;
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
    g.parallelBFS(start);
    double end_time = omp_get_wtime();

    cout << "Time: " << end_time - start_time << " sec\n";

    return 0;
}