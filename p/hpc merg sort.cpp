#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

/* -------- MERGE FUNCTION -------- */
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp;
    int i = l, j = m + 1;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= m) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++) {
        arr[l + k] = temp[k];
    }
}

/* -------- SEQUENTIAL MERGE SORT -------- */
void merge_sort_seq(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort_seq(arr, l, m);
        merge_sort_seq(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/* -------- PARALLEL MERGE SORT -------- */
void merge_sort_parallel(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            merge_sort_parallel(arr, l, m);

            #pragma omp section
            merge_sort_parallel(arr, m + 1, r);
        }

        merge(arr, l, m, r);
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
    merge_sort_seq(a1, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nSequential Time: " << end - start;

    // Parallel
    vector<int> a2 = arr;
    start = omp_get_wtime();
    merge_sort_parallel(a2, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nParallel Time: " << end - start;

    cout << "\nSorted Array:\n";
    for (int x : a2) cout << x << " ";

    return 0;
}







// Read [](file:///c%3A/Users/ADMIN/OneDrive/Desktop/hpc%20final/hpc%20merg%20sort.cpp)

// Below is a detailed, line-by-line explanation of the entire code in `hpc merg sort.cpp`. This is a C++ program implementing merge sort in sequential and parallel versions using OpenMP. Merge sort divides the array, sorts halves, and merges. The parallel version uses sections for concurrent sorting. It compares performance and outputs the sorted array.

// ### Line 1: `#include <iostream>`
// - **What it does**: Includes I/O library.
// - **Why needed**: For `cout` and `cin`.
// - **Details**: Standard.

// ### Line 2: `#include <vector>`
// - **What it does**: Includes vector.
// - **Why needed**: For dynamic arrays.
// - **Details**: STL.

// ### Line 3: `#include <omp.h>`
// - **What it does**: Includes OpenMP.
// - **Why needed**: For parallelism.
// - **Details**: Requires `-fopenmp`.

// ### Line 4: `using namespace std;`
// - **What it does**: Brings `std` into scope.
// - **Why needed**: Simplifies code.
// - **Details**: Common.

// ### Line 6: `/* -------- MERGE FUNCTION -------- */`
// - **What it does**: Comment for merge.
// - **Why needed**: Labels function.
// - **Details**: Merges two halves.

// ### Line 7: `void merge(vector<int>& arr, int l, int m, int r) {`
// - **What it does**: Defines merge function.
// - **Why needed**: Combines sorted halves.
// - **Details**: Takes array and indices.

// ### Line 8: `vector<int> temp;`
// - **What it does**: Temporary vector for merged result.
// - **Why needed**: Holds sorted elements.
// - **Details**: Empty initially.

// ### Line 9: `int i = l, j = m + 1;`
// - **What it does**: Pointers for left and right halves.
// - **Why needed**: Track positions.
// - **Details**: i for left, j for right.

// ### Line 11: `while (i <= m && j <= r) {`
// - **What it does**: Loops while both halves have elements.
// - **Why needed**: Merges until one half empty.
// - **Details**: Condition.

// ### Line 12: `if (arr[i] <= arr[j])`
// - **What it does**: Compares elements.
// - **Why needed**: Chooses smaller.
// - **Details**: Stable sort.

// ### Line 13: `temp.push_back(arr[i++]);`
// - **What it does**: Adds left element, increments i.
// - **Why needed**: Smaller from left.
// - **Details**: Push and increment.

// ### Line 14: `else`
// - **What it does**: If right smaller.
// - **Details**: Alternative.

// ### Line 15: `temp.push_back(arr[j++]);`
// - **What it does**: Adds right element, increments j.
// - **Why needed**: Smaller from right.
// - **Details**: Push and increment.

// ### Line 17: `while (i <= m) temp.push_back(arr[i++]);`
// - **What it does**: Adds remaining left elements.
// - **Why needed**: If right exhausted.
// - **Details**: Cleanup.

// ### Line 18: `while (j <= r) temp.push_back(arr[j++]);`
// - **What it does**: Adds remaining right elements.
// - **Why needed**: If left exhausted.
// - **Details**: Cleanup.

// ### Line 20: `for (int k = 0; k < temp.size(); k++) {`
// - **What it does**: Copies temp back to arr.
// - **Why needed**: Updates original array.
// - **Details**: Loop over temp.

// ### Line 21: `arr[l + k] = temp[k];`
// - **What it does**: Assigns from temp to arr.
// - **Why needed**: In-place merge.
// - **Details**: Offset by l.

// ### Line 22: `}`
// - **What it does**: Closes for.
// - **Details**: End.

// ### Line 23: `}`
// - **What it does**: Closes merge.
// - **Details**: End.

// ### Line 25: `/* -------- SEQUENTIAL MERGE SORT -------- */`
// - **What it does**: Comment for seq sort.
// - **Why needed**: Labels.
// - **Details**: Recursive.

// ### Line 26: `void merge_sort_seq(vector<int>& arr, int l, int r) {`
// - **What it does**: Defines seq merge sort.
// - **Why needed**: Sorts sequentially.
// - **Details**: Recursive.

// ### Line 27: `if (l < r) {`
// - **What it does**: Base case check.
// - **Why needed**: Stops at size 1.
// - **Details**: If l >= r, done.

// ### Line 28: `int m = (l + r) / 2;`
// - **What it does**: Finds midpoint.
// - **Why needed**: Splits array.
// - **Details**: Integer division.

// ### Line 29: `merge_sort_seq(arr, l, m);`
// - **What it does**: Sorts left half.
// - **Why needed**: Recursive call.
// - **Details**: Left subarray.

// ### Line 30: `merge_sort_seq(arr, m + 1, r);`
// - **What it does**: Sorts right half.
// - **Why needed**: Recursive call.
// - **Details**: Right subarray.

// ### Line 31: `merge(arr, l, m, r);`
// - **What it does**: Merges halves.
// - **Why needed**: Combines sorted parts.
// - **Details**: Call merge.

// ### Line 32: `}`
// - **What it does**: Closes if.
// - **Details**: End.

// ### Line 33: `}`
// - **What it does**: Closes function.
// - **Details**: End.

// ### Line 35: `/* -------- PARALLEL MERGE SORT -------- */`
// - **What it does**: Comment for parallel.
// - **Why needed**: Labels.
// - **Details**: OpenMP.

// ### Line 36: `void merge_sort_parallel(vector<int>& arr, int l, int r) {`
// - **What it does**: Defines parallel sort.
// - **Why needed**: Sorts with threads.
// - **Details**: Recursive.

// ### Line 37: `if (l < r) {`
// - **What it does**: Base case.
// - **Why needed**: Same as seq.
// - **Details**: Check.

// ### Line 38: `int m = (l + r) / 2;`
// - **What it does**: Midpoint.
// - **Why needed**: Split.
// - **Details**: Same.

// ### Line 40: `#pragma omp parallel sections`
// - **What it does**: Parallel sections.
// - **Why needed**: Concurrent execution.
// - **Details**: Threads for sections.

// ### Line 41: `{`
// - **What it does**: Opens sections.
// - **Details**: Block.

// ### Line 42: `#pragma omp section`
// - **What it does**: First section.
// - **Why needed**: Assigns to thread.
// - **Details**: Left sort.

// ### Line 43: `merge_sort_parallel(arr, l, m);`
// - **What it does**: Parallel left sort.
// - **Why needed**: Concurrent.
// - **Details**: Recursive.

// ### Line 45: `#pragma omp section`
// - **What it does**: Second section.
// - **Why needed**: Assigns to thread.
// - **Details**: Right sort.

// ### Line 46: `merge_sort_parallel(arr, m + 1, r);`
// - **What it does**: Parallel right sort.
// - **Why needed**: Concurrent.
// - **Details**: Recursive.

// ### Line 47: `}`
// - **What it does**: Closes sections.
// - **Details**: End.

// ### Line 49: `merge(arr, l, m, r);`
// - **What it does**: Merges after sections.
// - **Why needed**: Combines.
// - **Details**: Sequential merge.

// ### Line 50: `}`
// - **What it does**: Closes if.
// - **Details**: End.

// ### Line 51: `}`
// - **What it does**: Closes function.
// - **Details**: End.

// ### Line 53: `/* -------- MAIN -------- */`
// - **What it does**: Comment for main.
// - **Why needed**: Labels.
// - **Details**: Entry.

// ### Line 54: `int main() {`
// - **What it does**: Main function.
// - **Why needed**: Program start.
// - **Details**: Standard.

// ### Line 55: `int n;`
// - **What it does**: Size variable.
// - **Why needed**: Input.
// - **Details**: Int.

// ### Line 56: `cout << "Enter number of elements: ";`
// - **What it does**: Prompt n.
// - **Why needed**: Input.
// - **Details**: Output.

// ### Line 57: `cin >> n;`
// - **What it does**: Read n.
// - **Why needed**: Set size.
// - **Details**: Input.

// ### Line 58: `vector<int> arr(n);`
// - **What it does**: Create array.
// - **Why needed**: Holds elements.
// - **Details**: Size n.

// ### Line 59: `cout << "Enter elements:\n";`
// - **What it does**: Prompt elements.
// - **Why needed**: Input.
// - **Details**: Output.

// ### Line 60: `for (int i = 0; i < n; i++) cin >> arr[i];`
// - **What it does**: Read n elements.
// - **Why needed**: Populate array.
// - **Details**: Loop.

// ### Line 62: `omp_set_num_threads(4);`
// - **What it does**: Set threads to 4.
// - **Why needed**: Parallelism.
// - **Details**: Fixed.

// ### Line 64: `double start, end;`
// - **What it does**: Timing vars.
// - **Why needed**: Measure time.
// - **Details**: Doubles.

// ### Line 66: `// Sequential`
// - **What it does**: Comment.
// - **Why needed**: Labels.
// - **Details**: Baseline.

// ### Line 67: `vector<int> a1 = arr;`
// - **What it does**: Copy arr.
// - **Why needed**: Separate for seq.
// - **Details**: Avoid modify.

// ### Line 68: `start = omp_get_wtime();`
// - **What it does**: Start time.
// - **Why needed**: Timing.
// - **Details**: Timer.

// ### Line 69: `merge_sort_seq(a1, 0, n - 1);`
// - **What it does**: Seq sort.
// - **Why needed**: Execute.
// - **Details**: Full range.

// ### Line 70: `end = omp_get_wtime();`
// - **What it does**: End time.
// - **Why needed**: Timing.
// - **Details**: Timer.

// ### Line 71: `cout << "\nSequential Time: " << end - start;`
// - **What it does**: Print seq time.
// - **Why needed**: Performance.
// - **Details**: Output.

// ### Line 73: `// Parallel`
// - **What it does**: Comment.
// - **Why needed**: Labels.
// - **Details**: HPC.

// ### Line 74: `vector<int> a2 = arr;`
// - **What it does**: Copy arr.
// - **Why needed**: Separate for parallel.
// - **Details**: Copy.

// ### Line 75: `start = omp_get_wtime();`
// - **What it does**: Start time.
// - **Why needed**: Timing.
// - **Details**: Timer.

// ### Line 76: `merge_sort_parallel(a2, 0, n - 1);`
// - **What it does**: Parallel sort.
// - **Why needed**: Execute.
// - **Details**: Full range.

// ### Line 77: `end = omp_get_wtime();`
// - **What it does**: End time.
// - **Why needed**: Timing.
// - **Details**: Timer.

// ### Line 78: `cout << "\nParallel Time: " << end - start;`
// - **What it does**: Print parallel time.
// - **Why needed**: Comparison.
// - **Details**: Output.

// ### Line 80: `cout << "\nSorted Array:\n";`
// - **What it does**: Header.
// - **Why needed**: Labels result.
// - **Details**: Output.

// ### Line 81: `for (int x : a2) cout << x << " ";`
// - **What it does**: Print sorted array.
// - **Why needed**: Show result.
// - **Details**: Loop.

// ### Line 83: `return 0;`
// - **What it does**: Return success.
// - **Why needed**: Exit.
// - **Details**: Standard.

// ### Line 84: `}`
// - **What it does**: Closes main.
// - **Details**: End.

// ### Overall Notes
// - **Algorithm**: Merge sort: divide, conquer, merge. O(n log n) time/space.
// - **Parallelism**: Sections sort halves concurrently; merge sequential.
// - **Performance**: Compares times; parallel faster on large n with threads.
// - **Input/Output**: Interactive; reads n/elements, outputs times/array.

// If you need help or changes, let me know!


// Below is a list of expected viva questions and concise answers based on the merge sort code in `hpc merg sort.cpp`. Focused on sorting, OpenMP, and divide-conquer.

// ### 1. **What is merge sort?**
//    - **Answer**: A divide-and-conquer algorithm that splits the array, sorts halves recursively, and merges them.

// ### 2. **Explain the `merge` function.**
//    - **Answer**: Merges two sorted subarrays into one using a temp vector, comparing elements and copying back.

// ### 3. **How does sequential merge sort work?**
//    - **Answer**: Recursive: find mid, sort left/right halves, then merge. Base case: l >= r.

// ### 4. **Why `#pragma omp parallel sections`?**
//    - **Answer**: Allows concurrent execution of left and right sorts in separate sections.

// ### 5. **Why merge after sections?**
//    - **Answer**: Merge must be sequential to combine sorted halves without races.

// ### 6. **Complexity of merge sort?**
//    - **Answer**: O(n log n) time and space, better than O(n²) for large n.

// ### 7. **Why use vector for temp in merge?**
//    - **Answer**: Dynamic sizing and easy push/pop; avoids manual memory management.

// ### 8. **How is stability ensured?**
//    - **Answer**: `if (arr[i] <= arr[j])` preserves order of equal elements.

// ### 9. **Compare seq vs. parallel time.**
//    - **Answer**: Sequential: O(n log n). Parallel: Faster with threads, but overhead for small n.

// ### 10. **Why copy arrays (a1, a2) in main?**
//     - **Answer**: Preserves original for separate sorts without modifying it.

// ### 11. **What if sections not used?**
//     - **Answer**: Sorts sequentially, losing parallelism.

// ### 12. **Why `omp_set_num_threads(4)`?**
//     - **Answer**: Sets 4 threads; sections use up to that for concurrent tasks.

// ### 13. **Is merge sort in-place?**
//     - **Answer**: No, uses O(n) extra space for temp array.

// ### 14. **Best/worst case?**
//     - **Answer**: Always O(n log n), unlike quicksort's worst case.

// ### 15. **Why recursive?**
//     - **Answer**: Natural for divide-conquer; easy to parallelize at split points.