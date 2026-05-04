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