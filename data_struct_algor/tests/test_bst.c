#include <stdio.h>
#include "bst.h"

int test_bst() {
    printf("Testing Binary Search Tree: \n");

    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder (sorted): ");
    inorder_traversal(root);
    printf("\n");

    printf("Preorder: ");
    preorder_traversal(root);
    printf("\n");

    printf("Postorder: ");
    postorder_traversal(root);
    printf("\n");

    printf("Search for 40: %s\n", search(root, 40) ? "Found" : "Not Found");
    printf("Search for 90: %s\n", search(root, 90) ? "Found" : "Not Found");

    destroy_tree(root);
    return 0;
}