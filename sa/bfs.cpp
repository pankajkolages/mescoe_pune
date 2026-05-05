#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    int num_vertices, num_edges, source;

    cout << "Enter vertices, edges and source: ";
    cin >> num_vertices >> num_edges >> source;

    vector<vector<int>> adj_list(num_vertices + 1);

    // Input graph
    for (int i = 0; i < num_edges; i++) {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u); // undirected
    }

    vector<bool> visited(num_vertices + 1, false);
    vector<int> current_level, next_level;

    // Initialize
    current_level.push_back(source);
    visited[source] = true;

    cout << "BFS Traversal: ";

    while (!current_level.empty()) {

        next_level.clear();

        // Process current level in parallel
        #pragma omp parallel for
        for (int i = 0; i < current_level.size(); i++) {
            int node = current_level[i];

            // Print safely
            #pragma omp critical
            cout << node << " ";

            for (int neighbour : adj_list[node]) {

                bool added = false;

                // Protect visited check + update
                #pragma omp critical
                {
                    if (!visited[neighbour]) {
                        visited[neighbour] = true;
                        added = true;
                    }
                }

                if (added) {
                    // Push to next level safely
                    #pragma omp critical
                    next_level.push_back(neighbour);
                }
            }
        }

        // Move to next level
        current_level = next_level;
    }

    cout << endl;
    return 0;
}