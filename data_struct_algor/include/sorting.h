#ifndef SORTING_H
#define SORTING_H

// Function declarations for sorting algorithms
void bubble_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void quicksort(int arr[], int low, int high);
void merge_sort(int arr[], int left, int right);
void print_array(int arr[], int n);

// Helper functions
int partition(int arr[], int low, int high);
void merge(int arr[], int left, int mid, int right);

#endif