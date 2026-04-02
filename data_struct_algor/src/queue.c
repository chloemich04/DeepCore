#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*
 * Initialize the queue.
 @par
 */
void init_queue(Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

/*
 * Check if the queue is empty.
 @param queue = The queue to check.
 @return 1 if the queue is empty, 0 otherwise.
 */
int is_queue_empty(Queue* queue) {
    return queue->size == 0;
}

/*
 * Check if the queue is full.
 @param queue = The queue to check.
 @return 1 if the queue is full, 0 otherwise.
 */
int is_queue_full(Queue* queue) {
    return queue->size == MAX_QUEUE_SIZE;
}

/*
 * Enqueue an element into the queue.
 @param queue = The queue to enqueue into.
 @param value = The value to enqueue.
 */
void enqueue(Queue* queue, int value) {
    if (is_queue_full(queue)) {
        printf("Queue overflow!\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE; // wrap around
    queue->data[queue->rear] = value;
    queue-> size++;
}

/*
 * Dequeue an element from the queue.
 @param queue = The queue to dequeue from.
 @return The dequeued value, or -1 if the queue is empty.
 */
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

/*
 * Peek at the front element of the queue without dequeuing it.
 @param queue = The queue to peek at.
 @return The value at the front of the queue, or -1 if the queue is empty.
 */
int peek_queue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Queue is empty!\n)");
        return -1;
    }
    return queue->data[queue->front];
}