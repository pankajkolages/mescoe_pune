#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

// Function for Minimum using Parallel Reduction
void min_reduction(const vector<int>& arr) {
    int min_value = INT_MAX;

    #pragma omp parallel for reduction(min:min_value)
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }

    cout << "Minimum value: " << min_value << endl;
}

// Function for Maximum using Parallel Reduction
void max_reduction(const vector<int>& arr) {
    int max_value = INT_MIN;

    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    cout << "Maximum value: " << max_value << endl;
}

// Function for Sum using Parallel Reduction
void sum_reduction(const vector<int>& arr) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }

    cout << "Sum: " << sum << endl;
}

// Function for Average using Parallel Reduction
void average_reduction(const vector<int>& arr) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }

    double avg = (double)sum / arr.size();
    cout << "Average: " << avg << endl;
}

// Main function
int main() {
    vector<int> arr = {5, 2, 9, 1, 7, 6, 8, 3, 4};

    min_reduction(arr);
    max_reduction(arr);
    sum_reduction(arr);
    average_reduction(arr);

    return 0;
}