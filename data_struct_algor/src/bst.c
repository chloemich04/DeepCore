#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/*
 * Creates a new node with the given data.
 * @param data = The data for the new node.
 * Returns a pointer to the new node.
 */
Node* create_node(int data) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/*
 * Inserts a new node with the given data into the BST.
 * @param root = The root of the BST.
 * @param data = The data for the new node.
 * Returns a pointer to the root of the BST.
 */
Node* insert(Node* root, int data) {
    if (root == NULL) 
        return create_node(data);
    
    if (data < root->data) 
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root-> right, data);
    
    return root;
}

/*
 * Searches for a node with the given data in the BST.
 * @param root = The root of the BST.
 * @param data = The data to search for.
 * Returns 1 if the data is found, 0 otherwise.
 */
int search(Node* root, int data) {
    if (root == NULL)
        return 0;

    if (data == root->data)
        return 1;
    else if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

/*
 * Performs an inorder traversal of the BST and prints the data of each node.
 * @param root = The root of the BST.
 */
void inorder_traversal(Node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

/*
 * Performs a preorder traversal of the BST and prints the data of each node.
 * @param root = The root of the BST.
 */
void preorder_traversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

/*
 * Performs a postorder traversal of the BST and prints the data of each node.
 * @param root = The root of the BST.
 */
void postorder_traversal(Node* root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

/*
 * Destroys the entire BST and frees all allocated memory.
 * @param root = The root of the BST.
 */
void destroy_tree(Node* root) {
    if (root != NULL) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
    }
}