#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Merge Function
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    // Merge both arrays
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

// Sequential Merge Sort
void merge_sort_sequential(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort_sequential(arr, l, m);
        merge_sort_sequential(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort using OpenMP Tasks
void merge_sort_parallel(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp task shared(arr)
        {
            merge_sort_parallel(arr, l, m);
        }

        #pragma omp task shared(arr)
        {
            merge_sort_parallel(arr, m + 1, r);
        }

        #pragma omp taskwait
        merge(arr, l, m, r);
    }
}

// Wrapper for Parallel Execution
void parallel_merge_sort(vector<int>& arr) {
    #pragma omp parallel
    {
        #pragma omp single
        {
            merge_sort_parallel(arr, 0, arr.size() - 1);
        }
    }
}

// Utility function
void print_array(const vector<int>& arr) {
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> original = {5, 2, 9, 1, 7, 6, 8, 3, 4};

    vector<int> arr_seq = original;
    vector<int> arr_par = original;

    double start, end;

    // Sequential Merge Sort
    start = omp_get_wtime();
    merge_sort_sequential(arr_seq, 0, arr_seq.size() - 1);
    end = omp_get_wtime();
    cout << "Sequential Merge Sort Time: " << end - start << " seconds" << endl;

    // Parallel Merge Sort
    start = omp_get_wtime();
    parallel_merge_sort(arr_par);
    end = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << end - start << " seconds" << endl;

    // Output
    cout << "\nSorted Array (Sequential): ";
    print_array(arr_seq);

    cout << "Sorted Array (Parallel): ";
    print_array(arr_par);

    return 0;
}