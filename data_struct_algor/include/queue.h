#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 100

typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front; // index of front element
    int rear; // index where next element will be added
    int size; // current number of elements
} Queue;

void init_queue(Queue* queue);
int is_queue_empty(Queue* queue);
int is_queue_full(Queue* queue);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int peek_queue(Queue* queue);

#endif