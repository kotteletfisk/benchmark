#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to merge two halves
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    vector<int> leftArr(n1), rightArr(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    cout << "Merging from index " << left << " to " << right << endl;

    // Merge the temp arrays back into arr
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    cout << "Merged section: ";
    for (int x = left; x <= right; x++) {
        cout << arr[x] << " ";
    }
    cout << endl;
}

// Merge Sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        cout << "Splitting from index " << left << " to " << right << endl;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    // Generate a large array with random numbers
    const int SIZE = 10000;  // Small size for more visible print output in Docker
    vector<int> arr(SIZE);

    // Fill the array with random numbers
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;  // Random numbers between 0 and 99
    }

    // Print the initial array
    cout << "Unsorted Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Start time measurement
    auto start = high_resolution_clock::now();

    // Sort the array using Merge Sort
    mergeSort(arr, 0, SIZE - 1);

    // End time measurement
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Print the sorted array
    cout << "Sorted Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Print time taken
    cout << "Merge Sort completed for " << SIZE << " elements in " 
         << duration.count() << " ms" << endl;

    return 0;
}
