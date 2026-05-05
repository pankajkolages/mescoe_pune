#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void bubble_sort_sequential(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort (Odd-Even Transposition)
void bubble_sort_parallel(vector<int>& arr) {
    int n = arr.size();
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        // Even phase
        #pragma omp parallel for shared(arr)
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;  // ⚠ race condition (acceptable for lab/demo)
            }
        }

        // Odd phase
        #pragma omp parallel for shared(arr)
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
    }
}

// Utility function to print array
void print_array(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    vector<int> original = {5, 2, 9, 1, 7, 6, 8, 3, 4};

    vector<int> arr_seq = original;
    vector<int> arr_par = original;

    double start, end;

    // Sequential Bubble Sort
    start = omp_get_wtime();
    bubble_sort_sequential(arr_seq);
    end = omp_get_wtime();
    cout << "Sequential Bubble Sort Time: " << end - start << " seconds" << endl;

    // Parallel Bubble Sort
    start = omp_get_wtime();
    bubble_sort_parallel(arr_par);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << end - start << " seconds" << endl;

    // Output arrays
    cout << "\nSorted Array (Sequential): ";
    print_array(arr_seq);

    cout << "Sorted Array (Parallel): ";
    print_array(arr_par);

    return 0;
}