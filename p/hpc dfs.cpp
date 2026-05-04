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







// Read [](file:///c%3A/Users/ADMIN/OneDrive/Desktop/hpc%20final/hpc%20dfs.cpp)

// Below is a detailed, line-by-line explanation of the entire code in `hpc dfs.cpp`. This is a C++ program implementing a parallel Depth-First Search (DFS) traversal on an undirected graph using OpenMP tasks. DFS explores as deep as possible before backtracking. The parallel version uses tasks for concurrent exploration. It measures execution time.

// ### Line 1: `#include <iostream>`
// - **What it does**: Includes I/O library.
// - **Why needed**: For `cout` and `cin`.
// - **Details**: Standard.

// ### Line 2: `#include <vector>`
// - **What it does**: Includes vector container.
// - **Why needed**: For adjacency lists.
// - **Details**: STL.

// ### Line 3: `#include <omp.h>`
// - **What it does**: Includes OpenMP.
// - **Why needed**: For parallel tasks.
// - **Details**: Requires `-fopenmp`.

// ### Line 4: `using namespace std;`
// - **What it does**: Brings `std` into scope.
// - **Why needed**: Simplifies code.
// - **Details**: Common.

// ### Line 6: `class Graph {`
// - **What it does**: Defines `Graph` class.
// - **Why needed**: Encapsulates graph and DFS.
// - **Details**: OOP.

// ### Line 7: `int V;`
// - **What it does**: Vertex count.
// - **Why needed**: Graph size.
// - **Details**: Member.

// ### Line 8: `vector<vector<int>> adj;`
// - **What it does**: Adjacency list.
// - **Why needed**: Stores edges.
// - **Details**: Vector of vectors.

// ### Line 10: `public:`
// - **What it does**: Public access.
// - **Why needed**: Expose methods.
// - **Details**: Class specifier.

// ### Line 11: `Graph(int V) {`
// - **What it does**: Constructor.
// - **Why needed**: Initializes graph.
// - **Details**: Takes V.

// ### Line 12: `this->V = V;`
// - **What it does**: Sets V.
// - **Why needed**: Assigns size.
// - **Details**: Disambiguates.

// ### Line 13: `adj.resize(V + 1);`
// - **What it does**: Resizes adj to V+1.
// - **Why needed**: 1-based indices.
// - **Details**: Prepares lists.

// ### Line 15: `void addEdge(int u, int v) {`
// - **What it does**: Adds edge.
// - **Why needed**: Builds graph.
// - **Details**: Undirected.

// ### Line 16: `adj[u].push_back(v);`
// - **What it does**: Adds v to u's list.
// - **Why needed**: Edge u-v.
// - **Details**: Push.

// ### Line 17: `adj[v].push_back(u);`
// - **What it does**: Adds u to v's list.
// - **Why needed**: Symmetric.
// - **Details**: Push.

// ### Line 20: `/* -------- DFS UTILITY -------- */`
// - **What it does**: Comment for utility.
// - **Why needed**: Labels function.
// - **Details**: Recursive helper.

// ### Line 21: `void dfsUtil(int node, vector<bool>& visited) {`
// - **What it does**: Recursive DFS function.
// - **Why needed**: Explores from node.
// - **Details**: Takes node and visited.

// ### Line 22: `bool process = false;`
// - **What it does**: Flag for processing.
// - **Why needed**: Controls recursion.
// - **Details**: Local.

// ### Line 24: `#pragma omp critical`
// - **What it does**: Critical section.
// - **Why needed**: Protects visited and cout.
// - **Details**: Serializes.

// ### Line 25: `{`
// - **What it does**: Opens critical.
// - **Details**: Block.

// ### Line 26: `if (!visited[node]) {`
// - **What it does**: Checks if unvisited.
// - **Why needed**: First visit.
// - **Details**: Condition.

// ### Line 27: `visited[node] = true;`
// - **What it does**: Marks visited.
// - **Why needed**: Prevents re-visit.
// - **Details**: Set.

// ### Line 28: `cout << node << " ";`
// - **What it does**: Prints node.
// - **Why needed**: Output traversal.
// - **Details**: Space-separated.

// ### Line 29: `process = true;`
// - **What it does**: Sets flag.
// - **Why needed**: Proceed.
// - **Details**: True.

// ### Line 30: `}`
// - **What it does**: Closes if.
// - **Details**: End.

// ### Line 31: `}`
// - **What it does**: Closes critical.
// - **Details**: End.

// ### Line 33: `if (!process) return;`
// - **What it does**: Early return if visited.
// - **Why needed**: Avoids duplicate work.
// - **Details**: Skip.

// ### Line 36: `for (int neighbor : adj[node]) {`
// - **What it does**: Loops neighbors.
// - **Why needed**: Explores children.
// - **Details**: Range-based.

// ### Line 37: `#pragma omp task`
// - **What it does**: Creates task.
// - **Why needed**: Parallel recursion.
// - **Details**: Spawns thread for neighbor.

// ### Line 38: `dfsUtil(neighbor, visited);`
// - **What it does**: Recursive call.
// - **Why needed**: DFS on neighbor.
// - **Details**: Tasked.

// ### Line 39: `}`
// - **What it does**: Closes for.
// - **Details**: End.

// ### Line 40: `}`
// - **What it does**: Closes function.
// - **Details**: End.

// ### Line 42: `/* -------- PARALLEL DFS -------- */`
// - **What it does**: Comment for main DFS.
// - **Why needed**: Labels.
// - **Details**: Public method.

// ### Line 43: `void parallelDFS(int start) {`
// - **What it does**: Starts parallel DFS.
// - **Why needed**: Entry for traversal.
// - **Details**: Takes start.

// ### Line 44: `vector<bool> visited(V + 1, false);`
// - **What it does**: Initializes visited.
// - **Why needed**: Tracks nodes.
// - **Details**: False.

// ### Line 46: `cout << "\nParallel DFS Traversal: ";`
// - **What it does**: Header.
// - **Why needed**: Output.
// - **Details**: Print.

// ### Line 48: `#pragma omp parallel`
// - **What it does**: Parallel region.
// - **Why needed**: Threads.
// - **Details**: Creates team.

// ### Line 49: `{`
// - **What it does**: Opens parallel.
// - **Details**: Block.

// ### Line 50: `#pragma omp single`
// - **What it does**: Single thread executes.
// - **Why needed**: Starts DFS once.
// - **Details**: Avoids duplicates.

// ### Line 51: `dfsUtil(start, visited);`
// - **What it does**: Calls utility.
// - **Why needed**: Begins traversal.
// - **Details**: From start.

// ### Line 52: `}`
// - **What it does**: Closes parallel.
// - **Details**: End.

// ### Line 54: `cout << endl;`
// - **What it does**: Newline.
// - **Why needed**: Format.
// - **Details**: End output.

// ### Line 55: `}`
// - **What it does**: Closes method.
// - **Details**: End.

// ### Line 57: `};`
// - **What it does**: Closes class.
// - **Details**: End.

// ### Line 59: `int main() {`
// - **What it does**: Main function.
// - **Why needed**: Program start.
// - **Details**: Standard.

// ### Line 60: `int V, E;`
// - **What it does**: Variables for V and E.
// - **Why needed**: Input.
// - **Details**: Ints.

// ### Line 61: `cout << "Enter vertices: ";`
// - **What it does**: Prompt V.
// - **Why needed**: Input.
// - **Details**: Output.

// ### Line 62: `cin >> V;`
// - **What it does**: Read V.
// - **Why needed**: Set size.
// - **Details**: Input.

// ### Line 63: `Graph g(V);`
// - **What it does**: Create graph.
// - **Why needed**: Initialize.
// - **Details**: Constructor.

// ### Line 64: `cout << "Enter edges: ";`
// - **What it does**: Prompt E.
// - **Why needed**: Input.
// - **Details**: Output.

// ### Line 65: `cin >> E;`
// - **What it does**: Read E.
// - **Why needed**: Edge count.
// - **Details**: Input.

// ### Line 66: `for (int i = 0; i < E; i++) {`
// - **What it does**: Loop E times.
// - **Why needed**: Add edges.
// - **Details**: Input loop.

// ### Line 67: `int u, v;`
// - **What it does**: Edge vars.
// - **Why needed**: Temp.
// - **Details**: Ints.

// ### Line 68: `cin >> u >> v;`
// - **What it does**: Read u,v.
// - **Why needed**: Edge.
// - **Details**: Input.

// ### Line 69: `g.addEdge(u, v);`
// - **What it does**: Add edge.
// - **Why needed**: Build graph.
// - **Details**: Call.

// ### Line 70: `}`
// - **What it does**: Closes loop.
// - **Details**: End.

// ### Line 72: `int start;`
// - **What it does**: Start var.
// - **Why needed**: Root.
// - **Details**: Int.

// ### Line 73: `cout << "Start node: ";`
// - **What it does**: Prompt start.
// - **Why needed**: Input.
// - **Details**: Output.

// ### Line 74: `cin >> start;`
// - **What it does**: Read start.
// - **Why needed**: Set root.
// - **Details**: Input.

// ### Line 75: `omp_set_num_threads(4);`
// - **What it does**: Set threads to 4.
// - **Why needed**: Parallelism.
// - **Details**: Fixed.

// ### Line 77: `double start_time = omp_get_wtime();`
// - **What it does**: Start time.
// - **Why needed**: Timing.
// - **Details**: Timer.

// ### Line 78: `g.parallelDFS(start);`
// - **What it does**: Call DFS.
// - **Why needed**: Execute.
// - **Details**: Method.

// ### Line 79: `double end_time = omp_get_wtime();`
// - **What it does**: End time.
// - **Why needed**: Timing.
// - **Details**: Timer.

// ### Line 80: `cout << "Time: " << end_time - start_time << " sec\n";`
// - **What it does**: Print time.
// - **Why needed**: Performance.
// - **Details**: Output.

// ### Line 82: `return 0;`
// - **What it does**: Return success.
// - **Why needed**: Exit.
// - **Details**: Standard.

// ### Line 83: `}`
// - **What it does**: Closes main.
// - **Details**: End.

// ### Overall Notes
// - **Algorithm**: DFS explores depth-first with recursion. Parallel uses tasks for concurrent subtrees.
// - **Parallelism**: `#pragma omp task` spawns tasks for neighbors; critical protects shared data.
// - **Performance**: Measures time; tasks suit irregular parallelism but have overhead.
// - **Input/Output**: Interactive; reads V, E, edges, start; outputs traversal and time.

// If you need help or modifications, let me know!

// Below is a list of expected viva questions and concise answers based on the DFS code in `hpc dfs.cpp`. Focused on DFS, OpenMP tasks, and graph traversal.

// ### 1. **What is DFS?**
//    - **Answer**: Depth-First Search explores a graph by going deep into one path before backtracking.

// ### 2. **How is the graph represented?**
//    - **Answer**: Adjacency list using `vector<vector<int>> adj` for efficient neighbor access.

// ### 3. **Explain the `dfsUtil` function.**
//    - **Answer**: Recursive utility that marks node visited (critical), prints it, and spawns tasks for neighbors.

// ### 4. **Why `#pragma omp critical` in `dfsUtil`?**
//    - **Answer**: Protects `visited` array and `cout` from race conditions during concurrent access.

// ### 5. **What does `#pragma omp task` do?**
//    - **Answer**: Creates a task for each neighbor's DFS, allowing parallel exploration of subtrees.

// ### 6. **Why `#pragma omp single` in `parallelDFS`?**
//    - **Answer**: Ensures only one thread starts the initial DFS call to avoid duplicates.

// ### 7. **How does parallel DFS differ from sequential?**
//    - **Answer**: Sequential is single-threaded recursion. Parallel uses tasks for concurrent subtrees, faster on multi-core.

// ### 8. **What is the role of `visited` array?**
//    - **Answer**: Tracks visited nodes to prevent re-exploration and cycles.

// ### 9. **Why use tasks instead of parallel for?**
//    - **Answer**: DFS has irregular parallelism; tasks suit recursive, dynamic branching better than fixed loops.

// ### 10. **How is time measured?**
//     - **Answer**: `omp_get_wtime()` captures start/end times, difference shows execution duration.

// ### 11. **Potential issues with parallel DFS?**
//     - **Answer**: Race on `visited`; fixed by critical. Task overhead may slow small graphs.

// ### 12. **Why undirected graph?**
//     - **Answer**: `addEdge` adds both directions, suitable for bidirectional traversal.

// ### 13. **Complexity of DFS?**
//     - **Answer**: O(V + E) time/space for traversal, as each node/edge visited once.

// ### 14. **Why `omp_set_num_threads(4)`?**
//     - **Answer**: Sets thread count to 4 for controlled parallelism; default may vary.

// ### 15. **Is DFS traversal order deterministic?**
//     - **Answer**: Sequential yes; parallel no, due to task scheduling variations.
