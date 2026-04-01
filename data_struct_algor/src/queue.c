#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void init_queue(Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

int is_queue_empty(Queue* queue) {
    return queue->size == 0;
}

int is_queue_full(Queue* queue) {
    return queue->size == MAX_QUEUE_SIZE;
}

void enqueue(Queue* queue, int value) {
    if (is_queue_full(queue)) {
        printf("Queue overflow!\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE; // wrap around
    queue->data[queue->rear] = value;
    queue-> size++;
}

int dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Queue underflow!\n");
        return -1;
    }

    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE; // wrap around
    queue->size--;
    return value;
}

int peek_queue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Queue is empty!\n)");
        return -1;
    }
    return queue->data[queue->front];
}