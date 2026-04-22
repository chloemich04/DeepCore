#include <stdio.h>
#include <assert.h>
#include "sorting.h"

void test_bubble_sort() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]);

    printf("\n\n");
    

    bubble_sort(arr, n);

    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    for (int i = 0; i < n; i++) {
        assert(arr[i] == expected[i]);
    }

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]);

    printf("\n\n");
}

void test_insertion_sort() {
    int arr[] = {5, 2, 4, 6, 1, 3};
    int n = sizeof(arr)/ sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]);
    
    printf("\n\n");

    insertion_sort(arr, n);

    int expected[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < n; i++)
        assert(arr[i] == expected[i]);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]);

    printf("\n\n");
    
    //printf("Insertion sort test passed!\n");
}

void test_selection_sort() {
        int arr[] = {64, 25, 12, 22, 11};
        int n = sizeof(arr) / sizeof(arr[0]);
    
        printf("Original array: ");
        for (int i = 0; i < n; i++)
            printf(" %d ", arr[i]);
        
        printf("\n\n");
    
        selection_sort(arr, n);
    
        int expected[] = {11, 12, 22, 25, 64};
        for (int i = 0; i < n; i++)
            assert(arr[i] == expected[i]);
    
        printf("Sorted array: ");
        for (int i = 0; i < n; i++)
            printf(" %d ", arr[i]);
    
        printf("\n\n");
}

void test_quick_sort() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]);
    
    printf("\n\n");

    quicksort(arr, 0, n - 1);

    int expected[] = {1, 5, 7, 8, 9, 10};
    for (int i = 0; i < n; i++)
        assert(arr[i] == expected[i]);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]);

    printf("\n\n");
}

void test_merge_sort() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]);
    
    printf("\n\n");

    merge_sort(arr, 0, n - 1);

    int expected[] = {3, 9, 10, 27, 38, 43, 82};
    for (int i = 0; i < n; i++)
        assert(arr[i] == expected[i]);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf(" %d ", arr[i]);

    printf("\n\n");
}