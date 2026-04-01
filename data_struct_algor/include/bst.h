#ifndef BST_H
#define BST_H

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int data);
Node* insert(Node* root, int data);
int search(Node* root, int data);
void inorder_traversal(Node* root);
void preorder_traversal(Node* root);
void postorder_traversal(Node* root);
void destroy_tree(Node* root);

#endif
