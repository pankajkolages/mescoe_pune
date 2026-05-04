#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
using namespace std;

void min_reduction(vector<int>& arr) {
    int min_value = INT_MAX;
    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}

void max_reduction(vector<int>& arr) {
    int max_value = INT_MIN;
    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

void average_reduction(vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / arr.size() << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    min_reduction(arr);
    max_reduction(arr);
    sum_reduction(arr);
    average_reduction(arr);

    return 0;
}




// Read [](file:///c%3A/Users/ADMIN/OneDrive/Desktop/hpc%20final/hpc%20min%20max.cpp)

// Below is a detailed, line-by-line explanation of the entire code in `hpc min max.cpp`. This is a C++ program that computes minimum, maximum, sum, and average of an array using OpenMP reductions for parallelism. Reductions combine partial results from threads safely.

// ### Line 1: `#include <iostream>`
// - **What it does**: Includes I/O library.
// - **Why needed**: For `cout` and `cin`.
// - **Details**: Standard.

// ### Line 2: `#include <vector>`
// - **What it does**: Includes vector.
// - **Why needed**: For dynamic array.
// - **Details**: STL.

// ### Line 3: `#include <omp.h>`
// - **What it does**: Includes OpenMP.
// - **Why needed**: For parallel reductions.
// - **Details**: Requires `-fopenmp`.

// ### Line 4: `#include <climits>`
// - **What it does**: Includes limits.
// - **Why needed**: For `INT_MAX` and `INT_MIN`.
// - **Details**: Constants.

// ### Line 5: `using namespace std;`
// - **What it does**: Brings `std` into scope.
// - **Why needed**: Simplifies code.
// - **Details**: Common.

// ### Line 7: `void min_reduction(vector<int>& arr) {`
// - **What it does**: Defines min function.
// - **Why needed**: Finds minimum.
// - **Details**: Takes reference.

// ### Line 8: `int min_value = INT_MAX;`
// - **What it does**: Initializes min to max int.
// - **Why needed**: Start high for min.
// - **Details**: Largest int.

// ### Line 9: `#pragma omp parallel for reduction(min: min_value)`
// - **What it does**: Parallel loop with min reduction.
// - **Why needed**: Threads compute local mins, combine globally.
// - **Details**: Reduction operator.

// ### Line 10: `for (int i = 0; i < arr.size(); i++) {`
// - **What it does**: Loops over array.
// - **Why needed**: Check each element.
// - **Details**: Parallelized.

// ### Line 11: `if (arr[i] < min_value) {`
// - **What it does**: Compares with current min.
// - **Why needed**: Update if smaller.
// - **Details**: Local check.

// ### Line 12: `min_value = arr[i];`
// - **What it does**: Updates min.
// - **Why needed**: New minimum.
// - **Details**: Assign.

// ### Line 13: `}`
// - **What it does**: Closes if.
// - **Details**: End.

// ### Line 14: `}`
// - **What it does**: Closes for.
// - **Details**: End.

// ### Line 15: `cout << "Minimum value: " << min_value << endl;`
// - **What it does**: Prints min.
// - **Why needed**: Output result.
// - **Details**: Global min.

// ### Line 16: `}`
// - **What it does**: Closes function.
// - **Details**: End.

// ### Line 18: `void max_reduction(vector<int>& arr) {`
// - **What it does**: Defines max function.
// - **Why needed**: Finds maximum.
// - **Details**: Similar to min.

// ### Line 19: `int max_value = INT_MIN;`
// - **What it does**: Initializes max to min int.
// - **Why needed**: Start low for max.
// - **Details**: Smallest int.

// ### Line 20: `#pragma omp parallel for reduction(max: max_value)`
// - **What it does**: Parallel loop with max reduction.
// - **Why needed**: Threads combine maxes.
// - **Details**: Reduction.

// ### Line 21: `for (int i = 0; i < arr.size(); i++) {`
// - **What it does**: Loops array.
// - **Why needed**: Check elements.
// - **Details**: Parallel.

// ### Line 22: `if (arr[i] > max_value) {`
// - **What it does**: Compares with current max.
// - **Why needed**: Update if larger.
// - **Details**: Condition.

// ### Line 23: `max_value = arr[i];`
// - **What it does**: Updates max.
// - **Why needed**: New maximum.
// - **Details**: Assign.

// ### Line 24: `}`
// - **What it does**: Closes if.
// - **Details**: End.

// ### Line 25: `}`
// - **What it does**: Closes for.
// - **Details**: End.

// ### Line 26: `cout << "Maximum value: " << max_value << endl;`
// - **What it does**: Prints max.
// - **Why needed**: Output.
// - **Details**: Global max.

// ### Line 27: `}`
// - **What it does**: Closes function.
// - **Details**: End.

// ### Line 29: `void sum_reduction(vector<int>& arr) {`
// - **What it does**: Defines sum function.
// - **Why needed**: Computes total sum.
// - **Details**: Reduction.

// ### Line 30: `int sum = 0;`
// - **What it does**: Initializes sum to 0.
// - **Why needed**: Start value.
// - **Details**: Neutral for +.

// ### Line 31: `#pragma omp parallel for reduction(+: sum)`
// - **What it does**: Parallel loop with sum reduction.
// - **Why needed**: Threads add partial sums.
// - **Details**: + operator.

// ### Line 32: `for (int i = 0; i < arr.size(); i++) {`
// - **What it does**: Loops array.
// - **Why needed**: Add elements.
// - **Details**: Parallel.

// ### Line 33: `sum += arr[i];`
// - **What it does**: Adds element to sum.
// - **Why needed**: Accumulate.
// - **Details**: Local add.

// ### Line 34: `}`
// - **What it does**: Closes for.
// - **Details**: End.

// ### Line 35: `cout << "Sum: " << sum << endl;`
// - **What it does**: Prints sum.
// - **Why needed**: Output.
// - **Details**: Global sum.

// ### Line 36: `}`
// - **What it does**: Closes function.
// - **Details**: End.

// ### Line 38: `void average_reduction(vector<int>& arr) {`
// - **What it does**: Defines average function.
// - **Why needed**: Computes mean.
// - **Details**: Uses sum.

// ### Line 39: `int sum = 0;`
// - **What it does**: Initializes sum.
// - **Why needed**: Same as above.
// - **Details**: 0.

// ### Line 40: `#pragma omp parallel for reduction(+: sum)`
// - **What it does**: Parallel sum.
// - **Why needed**: Same reduction.
// - **Details**: +.

// ### Line 41: `for (int i = 0; i < arr.size(); i++) {`
// - **What it does**: Loops array.
// - **Why needed**: Add elements.
// - **Details**: Parallel.

// ### Line 42: `sum += arr[i];`
// - **What it does**: Adds to sum.
// - **Why needed**: Accumulate.
// - **Details**: Same.

// ### Line 43: `}`
// - **What it does**: Closes for.
// - **Details**: End.

// ### Line 44: `cout << "Average: " << (double)sum / arr.size() << endl;`
// - **What it does**: Prints average.
// - **Why needed**: Mean value.
// - **Details**: Cast to double.

// ### Line 45: `}`
// - **What it does**: Closes function.
// - **Details**: End.

// ### Line 47: `int main() {`
// - **What it does**: Main function.
// - **Why needed**: Program start.
// - **Details**: Standard.

// ### Line 48: `int n;`
// - **What it does**: Size variable.
// - **Why needed**: Input.
// - **Details**: Int.

// ### Line 49: `cout << "Enter number of elements: ";`
// - **What it does**: Prompt n.
// - **Why needed**: Input.
// - **Details**: Output.

// ### Line 50: `cin >> n;`
// - **What it does**: Read n.
// - **Why needed**: Set size.
// - **Details**: Input.

// ### Line 51: `vector<int> arr(n);`
// - **What it does**: Create array.
// - **Why needed**: Holds elements.
// - **Details**: Size n.

// ### Line 53: `cout << "Enter " << n << " elements:\n";`
// - **What it does**: Prompt elements.
// - **Why needed**: Input.
// - **Details**: Output.

// ### Line 54: `for (int i = 0; i < n; i++) {`
// - **What it does**: Loop n times.
// - **Why needed**: Read elements.
// - **Details**: Input loop.

// ### Line 55: `cin >> arr[i];`
// - **What it does**: Read element.
// - **Why needed**: Populate array.
// - **Details**: Input.

// ### Line 56: `}`
// - **What it does**: Closes loop.
// - **Details**: End.

// ### Line 58: `min_reduction(arr);`
// - **What it does**: Calls min function.
// - **Why needed**: Compute min.
// - **Details**: Execute.

// ### Line 59: `max_reduction(arr);`
// - **What it does**: Calls max function.
// - **Why needed**: Compute max.
// - **Details**: Execute.

// ### Line 60: `sum_reduction(arr);`
// - **What it does**: Calls sum function.
// - **Why needed**: Compute sum.
// - **Details**: Execute.

// ### Line 61: `average_reduction(arr);`
// - **What it does**: Calls average function.
// - **Why needed**: Compute average.
// - **Details**: Execute.

// ### Line 63: `return 0;`
// - **What it does**: Return success.
// - **Why needed**: Exit.
// - **Details**: Standard.

// ### Line 64: `}`
// - **What it does**: Closes main.
// - **Details**: End.

// ### Overall Notes
// - **Algorithm**: Uses OpenMP reductions for min, max, sum. Threads compute partial results, combined automatically.
// - **Parallelism**: `parallel for reduction` distributes work and merges results safely.
// - **Performance**: Faster for large arrays; reductions avoid manual synchronization.
// - **Input/Output**: Interactive; reads n/elements, outputs min/max/sum/avg.

// If you need help or changes, let me know!




// Below is a list of expected viva questions and concise answers based on the min/max code in `hpc min max.cpp`. Focused on reductions, OpenMP, and parallelism.

// ### 1. **What are OpenMP reductions?**
//    - **Answer**: Mechanisms to combine partial results from threads into a single global result safely.

// ### 2. **Explain `reduction(min: min_value)`.**
//    - **Answer**: Threads compute local mins; OpenMP combines them with min operator to get global minimum.

// ### 3. **Why initialize `min_value` to `INT_MAX`?**
//    - **Answer**: Ensures any array value is smaller, starting high for min reduction.

// ### 4. **How does max reduction work?**
//    - **Answer**: Similar to min; threads find local maxes, combined with max operator.

// ### 5. **Why `INT_MIN` for max?**
//    - **Answer**: Starts low so any value is larger, for max reduction.

// ### 6. **Explain sum reduction `reduction(+: sum)`.**
//    - **Answer**: Threads add partial sums; OpenMP combines with + to get total sum.

// ### 7. **Why average uses sum reduction?**
//    - **Answer**: Computes total sum in parallel, then divides by size for mean.

// ### 8. **What if no reduction?**
//    - **Answer**: Race conditions on shared variables; results incorrect.

// ### 9. **Why `parallel for`?**
//    - **Answer**: Distributes loop iterations across threads for concurrent processing.

// ### 10. **Performance benefit?**
//     - **Answer**: Faster for large arrays; threads process subsets, reductions merge efficiently.

// ### 11. **Why vector for array?**
//     - **Answer**: Dynamic sizing, easy access; STL convenience over raw arrays.

// ### 12. **Why `<climits>`?**
//     - **Answer**: Provides `INT_MAX`/`INT_MIN` for initializing min/max values.

// ### 13. **Is this in-place?**
//     - **Answer**: Yes, no extra space beyond variables; array unchanged.

// ### 14. **Thread safety?**
//     - **Answer**: Reductions handle it; no manual locks needed.

// ### 15. **Why cast to double in average?**
//     - **Answer**: Ensures floating-point division for accurate mean.