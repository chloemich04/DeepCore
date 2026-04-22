#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

// Bubble Sort: O(n²) - repeatedly swaps adjacent elements if they are in wrong order
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                print_array(arr, n);
            }
        }
    }
}

/* Insertion Sort: O(n²) - builds the final sorted array one item at a time */
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        print_array(arr, n);
    }
}

/* Selection Sort: O(n²) - repeatedly selects the minimum element from unsorted part and puts it at the beginning */
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;

        print_array(arr, n);
    }
}

/* Quick Sort: O(n log n) - picks an element as pivot and partitions the array around the pivot */
void quicksort(int arr[], int low, int high) {
    if (low < high) { 
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

/* Partition function for Quick Sort */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    print_array(arr, high + 1);
    return i + 1;
}

/* Merge function to merge two halves for Merge Sort */
void merge(int arr[], int left, int mid, int right) {
    int left_size = mid - left + 1;     // size of left subarray
    int right_size = right - mid;       // size of right subarray

    // temporary arrays to hold the left and right subarrays
    int *left_arr = (int *)malloc(left_size * sizeof(int));
    int *right_arr = (int *)malloc(right_size * sizeof(int));

    for (int i = 0; i < left_size; i++)
        left_arr[i] = arr[left + i];    // copying left subarray to temp array
    
    for (int j = 0; j < right_size; j++)
        right_arr[j] = arr[mid + 1 + j];    // copying right subarray to temp array

    int i = 0;  // pointer for left subarray
    int j = 0;  // pointer for right subarray
    int k = left; // pointer for main array (start position)

    while (i < left_size && j < right_size) {
        if (left_arr[i] <= right_arr[j]) {
            // if the current element of left subarray is smaller than
            // or equal to the current element of right subarray,
            // copy the element from left subarray to main array and
            // move the pointer of left subarray to the next element
            arr[k] = left_arr[i];   
            i++;
        }
        else {
            // if the current element of right subarray is smaller than
            // the current element of left subarray, copy the element from right subarray
            // to main array and move the pointer of right subarray to the next element
            arr[k] = right_arr[j];
            j++;
        }
        // move the main array pointer to the next position
        k++;
    }

    // copy the remaining elements from left subarray (if there's any)
    while (i < left_size) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < right_size) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }

    print_array(arr, right + 1);

    // free the dynamically allocated memory for temporary arrays
    free(left_arr);
    free(right_arr);


}

/* Merge Sort: O(n log n) - divides the array into halves, sorts them and then merges them back together */
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // get mid point

        merge_sort(arr, left, mid); // sort the left half
        merge_sort(arr, mid + 1, right); // sort the right half
        merge(arr, left, mid, right); // merge the sorted halves
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]);
    printf("\n");
}