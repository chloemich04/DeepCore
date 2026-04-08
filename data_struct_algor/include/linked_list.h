#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

LinkedList* create_list();
void destroy_list(LinkedList* list);
void append(LinkedList* list, int data);
void prepend(LinkedList* list, int data);
void insert_at(LinkedList* list, int data, int index);
int remove_at(LinkedList* list, int index);
int find(LinkedList* list, int data);
void print_list(LinkedList* list);
int get_size(LinkedList* list);

#endif