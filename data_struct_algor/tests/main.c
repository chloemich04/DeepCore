#include <stdio.h>

int test_linked_list();
int test_stack();
int test_queue();
int test_bst();
int test_bubble_sort();
int test_insertion_sort();
int test_selection_sort();
int test_quick_sort();
int test_merge_sort();

int main() {
    printf("Running all tests...\n-------------------------\n");

    /*test_linked_list();
    printf("\nLinked list completed!\n----------------\n");

    test_stack();
    printf("\nStack completed!\n----------------\n");

    test_queue();
    printf("\nQueue completed!\n----------------\n");

    test_bst();
    printf("\nBinary Search Tree completed!\n----------------\n"); */

    printf("\nTesting Bubble sort...\n-------------------------\n");
    test_bubble_sort();
    printf("\nBubble sort test completed!\n----------------\n");

    printf("\nTesting Insertion sort...\n-------------------------\n");
    test_insertion_sort();
    printf("\nInsertion sort test completed!\n----------------\n");

    printf("\nTesting Selection sort...\n-------------------------\n");
    test_selection_sort();
    printf("\nSelection sort test completed!\n----------------\n");

    printf("\nTesting Quick sort...\n-------------------------\n");
    test_quick_sort();
    printf("\nQuick sort test completed!\n----------------\n");

    printf("\nTesting Merge sort...\n-------------------------\n");
    test_merge_sort();
    printf("\nMerge sort test completed!\n----------------\n");

    printf("All tests completed successfully!\n");

    return 0;
}