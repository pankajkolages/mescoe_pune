#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

/* -------- SEQUENTIAL BUBBLE SORT -------- */
void bubble_sort_seq(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

/* -------- PARALLEL BUBBLE SORT -------- */
void bubble_sort_parallel(vector<int>& arr) {
    int n = arr.size();
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        // Odd phase
        #pragma omp parallel for
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                #pragma omp critical
                isSorted = false;
            }
        }

        // Even phase
        #pragma omp parallel for
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                #pragma omp critical
                isSorted = false;
            }
        }
    }
}

/* -------- MAIN -------- */
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    omp_set_num_threads(4);

    double start, end;

    // Sequential
    vector<int> a1 = arr;
    start = omp_get_wtime();
    bubble_sort_seq(a1);
    end = omp_get_wtime();
    cout << "\nSequential Time: " << end - start;

    // Parallel
    vector<int> a2 = arr;
    start = omp_get_wtime();
    bubble_sort_parallel(a2);
    end = omp_get_wtime();
    cout << "\nParallel Time: " << end - start;

    cout << "\nSorted Array:\n";
    for (int x : a2) cout << x << " ";

    return 0;
}




// Read [](file:///c%3A/Users/ADMIN/OneDrive/Desktop/hpc%20final/hpc%20bubble%20sort.cpp)

// Below is a detailed, line-by-line explanation of the entire code in `hpc bubble sort.cpp`. This is a C++ program implementing bubble sort in both sequential and parallel versions using OpenMP. Bubble sort repeatedly swaps adjacent elements if out of order. The parallel version uses odd-even transposition for multi-threading. It compares performance and outputs the sorted array.

// ### Line 1: `#include <iostream>`
// - **What it does**: Includes the standard I/O library.
// - **Why needed**: For `cout` and `cin` to handle input/output.
// - **Details**: Essential for console interactions.

// ### Line 2: `#include <vector>`
// - **What it does**: Includes the vector container.
// - **Why needed**: Used for dynamic arrays (`vector<int>& arr`).
// - **Details**: Provides resizable arrays for the array to sort.

// ### Line 3: `#include <omp.h>`
// - **What it does**: Includes OpenMP for parallel programming.
// - **Why needed**: Enables pragmas like `#pragma omp parallel for`.
// - **Details**: Requires compilation with OpenMP support (e.g., `-fopenmp`).

// ### Line 4: `using namespace std;`
// - **What it does**: Brings `std` namespace into scope.
// - **Why needed**: Allows shorthand for standard elements.
// - **Details**: Simplifies code (e.g., `vector` vs. `std::vector`).

// ### Line 6: `/* -------- SEQUENTIAL BUBBLE SORT -------- */`
// - **What it does**: Comment labeling the sequential function.
// - **Why needed**: Documents the code section.
// - **Details**: Indicates non-parallel version.

// ### Line 7: `void bubble_sort_seq(vector<int>& arr) {`
// - **What it does**: Defines the sequential bubble sort function, taking a reference to a vector.
// - **Why needed**: Sorts the array in-place sequentially.
// - **Details**: Pass-by-reference avoids copying.

// ### Line 8: `int n = arr.size();`
// - **What it does**: Gets the size of the array.
// - **Why needed**: Determines loop bounds.
// - **Details**: `n` is the number of elements.

// ### Line 9: `for (int i = 0; i < n - 1; i++) {`
// - **What it does**: Outer loop for each pass (0 to n-2).
// - **Why needed**: Each pass bubbles the largest element to the end.
// - **Details**: Runs n-1 times.

// ### Line 10: `for (int j = 0; j < n - i - 1; j++) {`
// - **What it does**: Inner loop for comparisons in the current pass.
// - **Why needed**: Compares adjacent elements, excluding already sorted ones.
// - **Details**: Shrinks by i each pass.

// ### Line 11: `if (arr[j] > arr[j + 1]) {`
// - **What it does**: Checks if current element is greater than next.
// - **Why needed**: Determines if swap is needed.
// - **Details**: Ascending order condition.

// ### Line 12: `swap(arr[j], arr[j + 1]);`
// - **What it does**: Swaps the two elements.
// - **Why needed**: Moves larger element right.
// - **Details**: Uses std::swap.

// ### Line 13: `}`
// - **What it does**: Closes the if block.
// - **Details**: End of swap check.

// ### Line 14: `}`
// - **What it does**: Closes the inner loop.
// - **Details**: End of pass.

// ### Line 15: `}`
// - **What it does**: Closes the outer loop.
// - **Details**: End of function.

// ### Line 17: `/* -------- PARALLEL BUBBLE SORT -------- */`
// - **What it does**: Comment for the parallel function.
// - **Why needed**: Labels the HPC version.
// - **Details**: Odd-even transposition sort.

// ### Line 18: `void bubble_sort_parallel(vector<int>& arr) {`
// - **What it does**: Defines the parallel bubble sort function.
// - **Why needed**: Sorts using OpenMP threads.
// - **Details**: Reference parameter.

// ### Line 19: `int n = arr.size();`
// - **What it does**: Gets array size.
// - **Why needed**: Loop bounds.
// - **Details**: Same as sequential.

// ### Line 20: `bool isSorted = false;`
// - **What it does**: Initializes a flag to track if sorted.
// - **Why needed**: Controls the while loop.
// - **Details**: Starts as false to enter loop.

// ### Line 22: `while (!isSorted) {`
// - **What it does**: Loops until no swaps occur.
// - **Why needed**: Continues until sorted.
// - **Details**: Termination condition.

// ### Line 23: `isSorted = true;`
// - **What it does**: Assumes sorted at start of pass.
// - **Why needed**: Reset for each iteration.
// - **Details**: Set to false if any swap happens.

// ### Line 25: `// Odd phase`
// - **What it does**: Comment for odd-indexed comparisons.
// - **Why needed**: Documents the phase.
// - **Details**: Part of odd-even sort.

// ### Line 26: `#pragma omp parallel for`
// - **What it does**: Parallelizes the following for loop.
// - **Why needed**: Distributes iterations across threads.
// - **Details**: Creates threads and divides work.

// ### Line 27: `for (int i = 0; i < n - 1; i += 2) {`
// - **What it does**: Loops over odd positions (0,2,4,...).
// - **Why needed**: Compares arr[i] and arr[i+1].
// - **Details**: Step by 2 for odd phase.

// ### Line 28: `if (arr[i] > arr[i + 1]) {`
// - **What it does**: Checks if swap needed.
// - **Why needed**: Same as sequential.
// - **Details**: Condition for swap.

// ### Line 29: `swap(arr[i], arr[i + 1]);`
// - **What it does**: Swaps elements.
// - **Why needed**: Bubbles larger to right.
// - **Details**: In-place.

// ### Line 30: `#pragma omp critical`
// - **What it does**: Serializes access to `isSorted`.
// - **Why needed**: Prevents race conditions on the flag.
// - **Details**: Only one thread modifies at a time.

// ### Line 31: `isSorted = false;`
// - **What it does**: Sets flag to false if swap occurred.
// - **Why needed**: Indicates unsorted state.
// - **Details**: Critical section.

// ### Line 32: `}`
// - **What it does**: Closes the if block.
// - **Details**: End of swap.

// ### Line 33: `}`
// - **What it does**: Closes the odd phase loop.
// - **Details**: End of parallel for.

// ### Line 35: `// Even phase`
// - **What it does**: Comment for even phase.
// - **Why needed**: Labels the phase.
// - **Details**: Even-indexed comparisons.

// ### Line 36: `#pragma omp parallel for`
// - **What it does**: Parallelizes the even loop.
// - **Why needed**: Same as odd phase.
// - **Details**: Threads handle even positions.

// ### Line 37: `for (int i = 1; i < n - 1; i += 2) {`
// - **What it does**: Loops over even positions (1,3,5,...).
// - **Why needed**: Compares arr[i] and arr[i+1].
// - **Details**: Starts at 1, step 2.

// ### Line 38: `if (arr[i] > arr[i + 1]) {`
// - **What it does**: Checks for swap.
// - **Why needed**: Same logic.
// - **Details**: Condition.

// ### Line 39: `swap(arr[i], arr[i + 1]);`
// - **What it does**: Swaps if needed.
// - **Why needed**: Bubbles.
// - **Details**: Swap.

// ### Line 40: `#pragma omp critical`
// - **What it does**: Critical for `isSorted`.
// - **Why needed**: Race protection.
// - **Details**: Serializes flag update.

// ### Line 41: `isSorted = false;`
// - **What it does**: Sets flag if swapped.
// - **Why needed**: Unsorted indicator.
// - **Details**: Critical.

// ### Line 42: `}`
// - **What it does**: Closes if.
// - **Details**: End.

// ### Line 43: `}`
// - **What it does**: Closes even loop.
// - **Details**: End.

// ### Line 44: `}`
// - **What it does**: Closes while loop.
// - **Details**: End of function.

// ### Line 46: `/* -------- MAIN -------- */`
// - **What it does**: Comment for main.
// - **Why needed**: Labels entry point.
// - **Details**: Program start.

// ### Line 47: `int main() {`
// - **What it does**: Defines main function.
// - **Why needed**: Program execution.
// - **Details**: Standard.

// ### Line 48: `int n;`
// - **What it does**: Declares n for array size.
// - **Why needed**: User input.
// - **Details**: Integer.

// ### Line 49: `cout << "Enter number of elements: ";`
// - **What it does**: Prompts for n.
// - **Why needed**: User input.
// - **Details**: Output.

// ### Line 50: `cin >> n;`
// - **What it does**: Reads n.
// - **Why needed**: Sets size.
// - **Details**: Input.

// ### Line 51: `vector<int> arr(n);`
// - **What it does**: Creates vector of size n.
// - **Why needed**: Holds elements.
// - **Details**: Dynamic array.

// ### Line 52: `cout << "Enter elements:\n";`
// - **What it does**: Prompts for elements.
// - **Why needed**: Input.
// - **Details**: Output.

// ### Line 53: `for (int i = 0; i < n; i++) cin >> arr[i];`
// - **What it does**: Reads n elements into arr.
// - **Why needed**: Populates array.
// - **Details**: Loop input.

// ### Line 55: `omp_set_num_threads(4);`
// - **What it does**: Sets OpenMP threads to 4.
// - **Why needed**: Controls parallelism.
// - **Details**: Fixed for demo.

// ### Line 57: `double start, end;`
// - **What it does**: Declares timing variables.
// - **Why needed**: For performance measurement.
// - **Details**: Doubles for time.

// ### Line 59: `// Sequential`
// - **What it does**: Comment for sequential sort.
// - **Why needed**: Labels section.
// - **Details**: Baseline.

// ### Line 60: `vector<int> a1 = arr;`
// - **What it does**: Copies arr to a1.
// - **Why needed**: Separate copy for sequential sort.
// - **Details**: Avoids modifying original.

// ### Line 61: `start = omp_get_wtime();`
// - **What it does**: Records start time.
// - **Why needed**: Timing begin.
// - **Details**: OpenMP timer.

// ### Line 62: `bubble_sort_seq(a1);`
// - **What it does**: Calls sequential sort on a1.
// - **Why needed**: Sorts sequentially.
// - **Details**: Function call.

// ### Line 63: `end = omp_get_wtime();`
// - **What it does**: Records end time.
// - **Why needed**: Timing end.
// - **Details**: Timer.

// ### Line 64: `cout << "\nSequential Time: " << end - start;`
// - **What it does**: Prints sequential time.
// - **Why needed**: Shows performance.
// - **Details**: Output.

// ### Line 66: `// Parallel`
// - **What it does**: Comment for parallel sort.
// - **Why needed**: Labels section.
// - **Details**: HPC version.

// ### Line 67: `vector<int> a2 = arr;`
// - **What it does**: Copies arr to a2.
// - **Why needed**: Separate for parallel.
// - **Details**: Copy.

// ### Line 68: `start = omp_get_wtime();`
// - **What it does**: Start time for parallel.
// - **Why needed**: Timing.
// - **Details**: Timer.

// ### Line 69: `bubble_sort_parallel(a2);`
// - **What it does**: Calls parallel sort on a2.
// - **Why needed**: Sorts in parallel.
// - **Details**: Function.

// ### Line 70: `end = omp_get_wtime();`
// - **What it does**: End time.
// - **Why needed**: Timing.
// - **Details**: Timer.

// ### Line 71: `cout << "\nParallel Time: " << end - start;`
// - **What it does**: Prints parallel time.
// - **Why needed**: Performance comparison.
// - **Details**: Output.

// ### Line 73: `cout << "\nSorted Array:\n";`
// - **What it does**: Header for output.
// - **Why needed**: Labels result.
// - **Details**: Output.

// ### Line 74: `for (int x : a2) cout << x << " ";`
// - **What it does**: Prints sorted array.
// - **Why needed**: Shows result.
// - **Details**: Range-based loop.

// ### Line 76: `return 0;`
// - **What it does**: Returns success.
// - **Why needed**: Exits program.
// - **Details**: Standard.

// ### Line 77: `}`
// - **What it does**: Closes main.
// - **Details**: End.

// ### Overall Notes
// - **Algorithm**: Bubble sort with O(n²) complexity. Parallel uses odd-even phases for thread safety.
// - **Parallelism**: Threads handle independent comparisons; critical sections protect shared flag.
// - **Performance**: Compares seq vs. parallel time; parallel may be faster on multi-core but has overhead.
// - **Input/Output**: Interactive; reads n and elements, outputs times and sorted array.

// If you need help running or modifying, let me know!






// Below is a list of expected viva questions and concise answers based on the bubble sort code in `hpc bubble sort.cpp`. Focused on sorting, OpenMP, and parallelism.

// ### 1. **What is bubble sort?**
//    - **Answer**: A simple sorting algorithm that repeatedly swaps adjacent elements if out of order, bubbling larger elements to the end.

// ### 2. **Explain the sequential bubble sort in the code.**
//    - **Answer**: Nested loops: outer for passes (n-1 times), inner for comparisons (shrinking by i). Swaps if arr[j] > arr[j+1].

// ### 3. **How does the parallel bubble sort work?**
//    - **Answer**: Uses odd-even transposition: odd phase compares/swaps even indices, even phase odd indices. Loops until no swaps.

// ### 4. **Why use `#pragma omp parallel for`?**
//    - **Answer**: Distributes loop iterations across threads for parallel execution of comparisons/swaps.

// ### 5. **What is the role of `#pragma omp critical`?**
//    - **Answer**: Serializes access to `isSorted` flag to prevent race conditions when updating it.

// ### 6. **Why odd-even phases in parallel sort?**
//    - **Answer**: Ensures independent comparisons per phase, avoiding conflicts between adjacent elements.

// ### 7. **How is sorting termination handled?**
//    - **Answer**: `isSorted` starts true each pass; set to false on swap. Loop ends when no swaps occur.

// ### 8. **Compare sequential vs. parallel time.**
//    - **Answer**: Sequential: O(n²). Parallel: Faster on multi-core due to threads, but overhead for small n.

// ### 9. **What happens without `omp_set_num_threads(4)`?**
//    - **Answer**: Uses default/system threads (often fewer), reducing parallelism.

// ### 10. **Why copy arrays (a1, a2) in main?**
//     - **Answer**: Preserves original `arr` for separate seq/parallel sorts without interference.

// ### 11. **Potential issues with parallel bubble sort?**
//     - **Answer**: Race on `isSorted`; fixed by critical. Overhead may outweigh gains for small arrays.

// ### 12. **Why use `omp_get_wtime()`?**
//     - **Answer**: Measures wall-clock time accurately for performance comparison.

// ### 13. **Is bubble sort stable?**
//     - **Answer**: Yes, preserves relative order of equal elements.

// ### 14. **Best/worst case for bubble sort?**
//     - **Answer**: Best: O(n) if sorted. Worst: O(n²) if reverse sorted.

// ### 15. **Why vector for array?**
//     - **Answer**: Dynamic sizing, easy copying, and STL convenience over raw arrays.