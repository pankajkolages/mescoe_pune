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




// Read [](file:///c%3A/Users/ADMIN/OneDrive/Desktop/hpc%20final/hpc%20bfs.cpp#1-1), lines 1 to 100

// Read [](file:///c%3A/Users/ADMIN/OneDrive/Desktop/hpc%20final/hpc%20bfs.cpp)

// Below is a detailed, line-by-line explanation of the entire code in `hpc bfs.cpp`. This is a C++ program implementing a parallel Breadth-First Search (BFS) traversal on an undirected graph using OpenMP for multi-threading. BFS explores nodes level by level, and the parallel version uses threads to process the frontier (current level) concurrently. The code uses adjacency lists for the graph and measures execution time.

// ### Line 1: `#include <iostream>`
// - **What it does**: Includes the standard I/O library for input/output operations like `cout` and `cin`.
// - **Why needed**: Enables console input (e.g., reading vertices/edges) and output (e.g., printing traversal and time).
// - **Details**: Part of the C++ standard library.

// ### Line 2: `#include <vector>`
// - **What it does**: Includes the vector container from the STL.
// - **Why needed**: Used for dynamic arrays like adjacency lists (`vector<vector<int>> adj`) and frontiers (`vector<int> frontier`).
// - **Details**: Provides resizable arrays, essential for graph representation.

// ### Line 3: `#include <omp.h>`
// - **What it does**: Includes the OpenMP header for parallel programming directives.
// - **Why needed**: Enables multi-threading with pragmas like `#pragma omp parallel`.
// - **Details**: Requires OpenMP support (e.g., compile with `-fopenmp` in GCC).

// ### Line 4: `using namespace std;`
// - **What it does**: Brings the `std` namespace into scope.
// - **Why needed**: Allows shorthand use of standard library elements (e.g., `vector` instead of `std::vector`).
// - **Details**: Common in C++ for simplicity.

// ### Line 6: `class Graph {`
// - **What it does**: Defines a `Graph` class to represent an undirected graph.
// - **Why needed**: Encapsulates graph data (vertices, edges) and operations (add edge, BFS).
// - **Details**: Object-oriented design for modularity.

// ### Line 7: `int V;`
// - **What it does**: Declares an integer `V` for the number of vertices.
// - **Why needed**: Stores graph size.
// - **Details**: Private member variable.

// ### Line 8: `vector<vector<int>> adj;`
// - **What it does**: Declares an adjacency list: a vector of vectors, where each index represents a vertex and holds its neighbors.
// - **Why needed**: Represents the graph's edges efficiently.
// - **Details**: `adj[u]` contains neighbors of vertex `u`.

// ### Line 10: `public:`
// - **What it does**: Marks the following members as public (accessible outside the class).
// - **Why needed**: Allows `main` to create graphs and call methods.
// - **Details**: Standard class access specifier.

// ### Line 11: `Graph(int V) {`
// - **What it does**: Constructor for `Graph`, taking vertices `V`.
// - **Why needed**: Initializes the graph with `V` vertices.
// - **Details**: Called as `Graph g(V);`.

// ### Line 12: `this->V = V;`
// - **What it does**: Assigns the parameter `V` to the member `V`.
// - **Why needed**: Sets the vertex count.
// - **Details**: `this->` disambiguates the member from the parameter.

// ### Line 13: `adj.resize(V + 1);`
// - **What it does**: Resizes `adj` to `V+1` vectors (indices 1 to V, assuming 1-based vertices).
// - **Why needed**: Prepares space for adjacency lists.
// - **Details**: Index 0 is unused for simplicity.

// ### Line 15: `void addEdge(int u, int v) {`
// - **What it does**: Method to add an undirected edge between `u` and `v`.
// - **Why needed**: Builds the graph.
// - **Details**: Public method.

// ### Line 16: `adj[u].push_back(v);`
// - **What it does**: Adds `v` to `u`'s neighbor list.
// - **Why needed**: Represents the edge from `u` to `v`.
// - **Details**: Undirected, so also adds `u` to `v`.

// ### Line 17: `adj[v].push_back(u);`
// - **What it does**: Adds `u` to `v`'s neighbor list.
// - **Why needed**: Completes the undirected edge.
// - **Details**: Ensures symmetry.

// ### Line 20: `/* -------- PARALLEL BFS -------- */`
// - **What it does**: Comment labeling the parallel BFS method.
// - **Why needed**: Documents the function.
// - **Details**: Indicates HPC focus.

// ### Line 21: `void parallelBFS(int start) {`
// - **What it does**: Defines the parallel BFS method, starting from vertex `start`.
// - **Why needed**: Performs the traversal using OpenMP.
// - **Details**: Public method.

// ### Line 22: `vector<bool> visited(V + 1, false);`
// - **What it does**: Initializes a visited array (size `V+1`) to `false`.
// - **Why needed**: Tracks visited nodes to avoid re-processing.
// - **Details**: 1-based indexing.

// ### Line 23: `vector<int> frontier, next_frontier;`
// - **What it does**: Declares two vectors for the current and next level frontiers.
// - **Why needed**: Manages BFS levels (queue-like).
// - **Details**: `frontier` is current level, `next_frontier` is next.

// ### Line 25: `frontier.push_back(start);`
// - **What it does**: Adds the start node to the initial frontier.
// - **Why needed**: Begins BFS from `start`.
// - **Details**: Level 0.

// ### Line 26: `visited[start] = true;`
// - **What it does**: Marks `start` as visited.
// - **Why needed**: Prevents revisiting.
// - **Details**: Ensures no cycles in traversal.

// ### Line 28: `cout << "\nParallel BFS Traversal: ";`
// - **What it does**: Prints a header for the output.
// - **Why needed**: User feedback.
// - **Details**: Console output.

// ### Line 30: `while (!frontier.empty()) {`
// - **What it does**: Loops while there are nodes to process.
// - **Why needed**: Continues until all reachable nodes are visited.
// - **Details**: BFS termination condition.

// ### Line 31: `next_frontier.clear();`
// - **What it does**: Clears the next frontier for the new level.
// - **Why needed**: Resets for each iteration.
// - **Details**: Prepares for next level's nodes.

// ### Line 33: `#pragma omp parallel`
// - **What it does**: Starts a parallel region with multiple threads.
// - **Why needed**: Enables multi-threading for concurrent processing.
// - **Details**: Threads share data but have private stacks.

// ### Line 34: `{`
// - **What it does**: Opens the parallel block.
// - **Why needed**: Groups parallel code.
// - **Details**: Scope for pragmas.

// ### Line 35: `vector<int> local_next;`
// - **What it does**: Declares a thread-local vector for next frontier candidates.
// - **Why needed**: Avoids race conditions by collecting locally first.
// - **Details**: Each thread has its own `local_next`.

// ### Line 37: `#pragma omp for nowait`
// - **What it does**: Distributes the loop iterations across threads without waiting at the end.
// - **Why needed**: Parallelizes processing of the current frontier.
// - **Details**: `nowait` allows threads to proceed asynchronously.

// ### Line 38: `for (int i = 0; i < frontier.size(); i++) {`
// - **What it does**: Loops over each node in the current frontier.
// - **Why needed**: Processes each node in the level.
// - **Details**: Parallelized loop.

// ### Line 39: `int node = frontier[i];`
// - **What it does**: Gets the current node from the frontier.
// - **Why needed**: Focuses on this node's neighbors.
// - **Details**: Local variable.

// ### Line 41: `#pragma omp critical`
// - **What it does**: Ensures only one thread executes the block at a time.
// - **Why needed**: Prevents interleaved output.
// - **Details**: Serializes `cout`.

// ### Line 42: `cout << node << " ";`
// - **What it does**: Prints the current node.
// - **Why needed**: Shows traversal order.
// - **Details**: Critical section for thread safety.

// ### Line 45: `for (int neighbor : adj[node]) {`
// - **What it does**: Loops over neighbors of `node`.
// - **Why needed**: Explores adjacent nodes.
// - **Details**: Range-based for loop.

// ### Line 46: `bool add = false;`
// - **What it does**: Initializes a flag for adding to next frontier.
// - **Why needed**: Decides if neighbor should be added.
// - **Details**: Thread-local.

// ### Line 48: `#pragma omp critical`
// - **What it does**: Critical section for shared data access.
// - **Why needed**: Protects `visited` from race conditions.
// - **Details**: Only one thread checks/modifies at a time.

// ### Line 49: `{`
// - **What it does**: Opens the critical block.
// - **Details**: Groups the check.

// ### Line 50: `if (!visited[neighbor]) {`
// - **What it does**: Checks if neighbor is unvisited.
// - **Why needed**: Ensures first-visit.
// - **Details**: BFS property.

// ### Line 51: `visited[neighbor] = true;`
// - **What it does**: Marks neighbor as visited.
// - **Why needed**: Prevents future visits.
// - **Details**: Sets flag.

// ### Line 52: `add = true;`
// - **What it does**: Sets flag to add to frontier.
// - **Why needed**: Indicates valid addition.
// - **Details**: Outside critical for efficiency.

// ### Line 53: `}`
// - **What it does**: Closes the if block.
// - **Details**: End of check.

// ### Line 54: `}`
// - **What it does**: Closes the critical block.
// - **Details**: End of protection.

// ### Line 56: `if (add) {`
// - **What it does**: If flag is set, add to local next.
// - **Why needed**: Collects unvisited neighbors.
// - **Details**: Thread-safe via local vector.

// ### Line 57: `local_next.push_back(neighbor);`
// - **What it does**: Adds neighbor to thread's local list.
// - **Why needed**: Builds next frontier candidates.
// - **Details**: No shared access here.

// ### Line 58: `}`
// - **What it does**: Closes the if block.
// - **Details**: End of addition.

// ### Line 59: `}`
// - **What it does**: Closes the neighbor loop.
// - **Details**: End of exploration.

// ### Line 60: `}`
// - **What it does**: Closes the frontier loop.
// - **Details**: End of parallel for.

// ### Line 62: `#pragma omp critical`
// - **What it does**: Critical section for merging local lists.
// - **Why needed**: Protects `next_frontier` from concurrent writes.
// - **Details**: Serializes the merge.

// ### Line 63: `next_frontier.insert(next_frontier.end(),`
// - **What it does**: Inserts `local_next` into `next_frontier`.
// - **Why needed**: Merges thread-local results.
// - **Details**: Appends to the end.

// ### Line 64: `local_next.begin(),`
// - **What it does**: Specifies start of range to insert.
// - **Details**: Iterator.

// ### Line 65: `local_next.end());`
// - **What it does**: Specifies end of range.
// - **Details**: Iterator.

// ### Line 66: `}`
// - **What it does**: Closes the critical block.
// - **Details**: End of merge.

// ### Line 67: `}`
// - **What it does**: Closes the parallel block.
// - **Details**: End of parallel region.

// ### Line 69: `frontier = next_frontier;`
// - **What it does**: Updates frontier to the next level.
// - **Why needed**: Prepares for next iteration.
// - **Details**: Swaps levels.

// ### Line 70: `}`
// - **What it does**: Closes the while loop.
// - **Details**: End of BFS.

// ### Line 72: `cout << endl;`
// - **What it does**: Prints a newline.
// - **Why needed**: Formats output.
// - **Details**: Ends the traversal print.

// ### Line 73: `}`
// - **What it does**: Closes the method.
// - **Details**: End of `parallelBFS`.

// ### Line 75: `};`
// - **What it does**: Closes the class.
// - **Details**: End of `Graph`.

// ### Line 77: `int main() {`
// - **What it does**: Program entry point.
// - **Why needed**: Executes the code.
// - **Details**: Standard C++ main.

// ### Line 78: `int V, E;`
// - **What it does**: Declares variables for vertices and edges.
// - **Why needed**: User input.
// - **Details**: Integers.

// ### Line 80: `cout << "Enter vertices: ";`
// - **What it does**: Prompts for vertex count.
// - **Why needed**: User input.
// - **Details**: Output.

// ### Line 81: `cin >> V;`
// - **What it does**: Reads `V` from input.
// - **Why needed**: Sets graph size.
// - **Details**: Input.

// ### Line 83: `Graph g(V);`
// - **What it does**: Creates a `Graph` object with `V` vertices.
// - **Why needed**: Initializes the graph.
// - **Details**: Constructor call.

// ### Line 85: `cout << "Enter edges: ";`
// - **What it does**: Prompts for edge count.
// - **Why needed**: User input.
// - **Details**: Output.

// ### Line 86: `cin >> E;`
// - **What it does**: Reads `E` from input.
// - **Why needed**: Number of edges to add.
// - **Details**: Input.

// ### Line 88: `for (int i = 0; i < E; i++) {`
// - **What it does**: Loops `E` times to add edges.
// - **Why needed**: Builds the graph.
// - **Details**: Input loop.

// ### Line 89: `int u, v;`
// - **What it does**: Declares edge endpoints.
// - **Why needed**: Temporary variables.
// - **Details**: Integers.

// ### Line 90: `cin >> u >> v;`
// - **What it does**: Reads `u` and `v` for the edge.
// - **Why needed**: Edge data.
// - **Details**: Input.

// ### Line 91: `g.addEdge(u, v);`
// - **What it does**: Adds the edge to the graph.
// - **Why needed**: Updates adjacency list.
// - **Details**: Method call.

// ### Line 92: `}`
// - **What it does**: Closes the edge loop.
// - **Details**: End of input.

// ### Line 94: `int start;`
// - **What it does**: Declares start node.
// - **Why needed**: BFS starting point.
// - **Details**: Integer.

// ### Line 95: `cout << "Start node: ";`
// - **What it does**: Prompts for start node.
// - **Why needed**: User input.
// - **Details**: Output.

// ### Line 96: `cin >> start;`
// - **What it does**: Reads `start` from input.
// - **Why needed**: Sets BFS root.
// - **Details**: Input.

// ### Line 98: `omp_set_num_threads(4);`
// - **What it does**: Sets the number of OpenMP threads to 4.
// - **Why needed**: Controls parallelism.
// - **Details**: Fixed for demo; can be dynamic.

// ### Line 100: `double start_time = omp_get_wtime();`
// - **What it does**: Records the start time using OpenMP's wall-clock timer.
// - **Why needed**: Measures execution time.
// - **Details**: High-precision timer.

// ### Line 101: `g.parallelBFS(start);`
// - **What it does**: Calls the parallel BFS method.
// - **Why needed**: Executes the traversal.
// - **Details**: Method invocation.

// ### Line 102: `double end_time = omp_get_wtime();`
// - **What it does**: Records the end time.
// - **Why needed**: Completes timing.
// - **Details**: Wall-clock.

// ### Line 104: `cout << "Time: " << end_time - start_time << " sec\n";`
// - **What it does**: Prints the elapsed time.
// - **Why needed**: Shows performance.
// - **Details**: Difference in seconds.

// ### Line 106: `return 0;`
// - **What it does**: Returns success code.
// - **Why needed**: Exits the program.
// - **Details**: Standard.

// ### Line 107: `}`
// - **What it does**: Closes `main`.
// - **Details**: End of program.

// ### Overall Notes
// - **Algorithm**: Parallel BFS uses frontiers and threads to explore levels concurrently, with critical sections for shared data.
// - **Parallelism**: Threads process frontier nodes in parallel, but merging uses critical sections to avoid races.
// - **Performance**: Measures time; parallelism speeds up for large graphs but has overhead.
// - **Input/Output**: Interactive; expects vertices, edges, and start node.
// - **Potential Issues**: Race conditions mitigated by critical sections; assumes 1-based vertices.

// If you need help running it or modifications, let me know!


// Below is a list of expected viva (oral examination) questions and answers based on the parallel BFS code in `hpc bfs.cpp`. These are typical questions for an HPC or parallel algorithms course, covering BFS theory, OpenMP usage, and the code's implementation. Answers are concise but detailed.

// ### 1. **What is BFS, and how does this code implement it?**
//    - **Answer**: BFS (Breadth-First Search) is a graph traversal algorithm that explores nodes level by level using a queue. This code uses a frontier (vector) for the current level and a next_frontier for the next, processing levels iteratively. It starts from a given node, marks it visited, and explores neighbors.

// ### 2. **Explain the role of the frontier in this parallel BFS.**
//    - **Answer**: The frontier represents the current level of nodes to process. `frontier` holds nodes at the same depth; `next_frontier` collects their unvisited neighbors. After processing a level, `frontier` is updated to `next_frontier`. This ensures level-order traversal.

// ### 3. **Why is the graph represented using adjacency lists?**
//    - **Answer**: Adjacency lists (`vector<vector<int>> adj`) store neighbors efficiently for sparse graphs. Each vertex has a list of connected nodes, allowing O(1) access to neighbors. It's better than matrices for large, sparse graphs, as used in BFS.

// ### 4. **How does OpenMP parallelize the BFS in this code?**
//    - **Answer**: `#pragma omp parallel` creates threads. `#pragma omp for nowait` distributes frontier processing across threads. Each thread explores a subset of nodes, collects local next-frontier candidates, and merges them critically to avoid races.

// ### 5. **What is the purpose of `#pragma omp critical` in the code?**
//    - **Answer**: It serializes access to shared resources like `visited` array and `cout` to prevent race conditions. For `visited`, it ensures only one thread marks a node visited. For output, it avoids interleaved prints.

// ### 6. **Why use `local_next` in the parallel region?**
//    - **Answer**: Each thread has a private `local_next` to collect neighbors without shared access, reducing contention. It's merged into `next_frontier` in a critical section, improving performance by minimizing locks.

// ### 7. **How does the code handle visited nodes to avoid cycles?**
//    - **Answer**: `vector<bool> visited(V + 1, false);` tracks visited nodes. Before adding a neighbor, a critical check (`if (!visited[neighbor])`) marks it visited if unvisited. This ensures each node is processed once, preventing infinite loops in cyclic graphs.

// ### 8. **Explain the timing measurement using `omp_get_wtime()`.**
//    - **Answer**: `omp_get_wtime()` provides high-precision wall-clock time. `start_time` and `end_time` capture before/after BFS, and the difference shows execution time. It's OpenMP-specific for parallel performance analysis.

// ### 9. **What happens if `omp_set_num_threads(4)` is removed?**
//    - **Answer**: The code runs serially (1 thread) by default. Parallelism is lost, making it slower for large graphs. OpenMP uses system defaults or environment variables if not set.

// ### 10. **Compare serial vs. parallel BFS performance.**
//     - **Answer**: Serial BFS processes nodes sequentially (O(V + E) time). Parallel uses threads for frontier processing, reducing time on multi-core systems but with overhead from synchronization. For dense graphs, parallelism helps; for small ones, overhead may dominate.

// ### 11. **Why is `nowait` used in `#pragma omp for`?**
//     - **Answer**: `nowait` allows threads to proceed without waiting at the loop end, enabling asynchronous execution. It improves performance by overlapping computation and merging.

// ### 12. **What are potential race conditions in this code, and how are they fixed?**
//     - **Answer**: Races on `visited` and `next_frontier` could cause duplicates or misses. Fixed with `#pragma omp critical` for atomic checks and merges. Output races are also criticalized.

// ### 13. **How does the code ensure thread safety for the adjacency list access?**
//     - **Answer**: Adjacency lists are read-only during BFS, so no locks needed. Writes happen only in `addEdge` (before BFS). Neighbor iteration is thread-local.

// ### 14. **What is the time complexity of this parallel BFS?**
//     - **Answer**: Worst-case O(V + E) like serial BFS, but with parallelism, it can approach O((V + E)/P) on P processors. Synchronization adds overhead, so benefits depend on graph size and cores.

// ### 15. **Why use `vector` instead of `queue` for frontiers?**
//     - **Answer**: Vectors allow random access and easy parallel iteration (`for (int i = 0; i < frontier.size(); i++)`). Queues are FIFO but harder to parallelize. Vectors suit level-based processing.

// If you need more questions or focus on a specific part, let me know! Practice explaining these for your viva.