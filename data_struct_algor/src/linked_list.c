#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/*
 * Creates a new linked list.
 * Returns a pointer to the new list.
 */
LinkedList* create_list() {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

/*
 * Destroys a linked list and frees all its memory.
 * @param list = The list to destroy.
 */
void destroy_list(LinkedList* list) {
    Node* current = list->head;
    
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

/*
 * Appends a new node with the given data to the end of the list.
 * @param = list The list to append to.
 * @param = data The data for the new node.
 */
void append(LinkedList* list, int data) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) 
        list->head = new_node;
    
    else {
        Node* current = list->head;

        while (current->next != NULL)
            current = current->next;
        
        current->next = new_node;
    }
    list->size++;
}

/*
 * Prints the contents of the linked list.
 * @param list = The list to print.
 */
void print_list(LinkedList* list) {
    Node* current = list->head;

    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

/*
 * Gets the size of the linked list.
 * @param list = The list to get the size of.
 * @return The size of the list.
 */
int get_size(LinkedList* list) {
    return list->size;
}

/*
 * Prepends a new node with the given data to the beginning of the list.
 * @param list = The list to prepend to.
 * @param data = The data for the new node.
 */
void prepend(LinkedList* list, int data) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

/**
 * Inserts a new node with the given data at the specified index in the list.
 * @param list = The list to insert into.
 * @param data = The data for the new node.
 * @param index = The index at which to insert the new node.
 */
void insert_at(LinkedList* list, int data, int index) {
    if (index < 0 || index > list->size) return;

    if (index == 0) {
        prepend(list, data);
        return;
    }

    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;

    Node* current = list->head;
    for (int i = 0; i < index - 1; i++)
        current = current->next;
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
}

/**
 * Removes the node at the specified index from the list.
 * @param list = The list to remove from.
 * @param index = The index of the node to remove.
 * @return The data of the removed node, or -1 if the index is invalid.
 */
int remove_at(LinkedList* list, int index) {
    if (index < - 0 || index >= list->size) return -1;

    Node* to_remove;
    int data;

    if (index == 0) {
        to_remove = list->head;
        list->head = to_remove->next;
    }

    else {
        Node* current = list->head;
        for(int i = 0; i < index - 1; i++)
            current = current->next;
        
        to_remove = current->next;
        current->next = to_remove->next;
    }

    data = to_remove->data;
    free(to_remove);
    list->size--;
    return data;
}

/**
 * Finds the index of the first occurrence of the given data in the list.
 * @param list = The list to search.
 * @param data = The data to search for.
 * @return The index of the first occurrence of the data, or -1 if not found.
 */
int find(LinkedList* list, int data) {
    Node* current = list->head;
    int index = 0;

    while (current != NULL) {
        if(current->data == data)
            return index;
        current = current->next;
        index++;
    }
    return -1;
     
}
