#include <stdio.h>
#include "queue.h"

int test_queue() {
    Queue queue;
    init_queue(&queue);

    printf("Testing Queue:\n");
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Peek: %d\n", peek_queue(&queue)); // Should print 10
    printf("Dequeue: %d\n", dequeue(&queue)); // Should print 10
    printf("Dequeue: %d\n", dequeue(&queue)); // Should print 20
    printf("Peek: %d\n", peek_queue(&queue)); // Should print 30
    printf("Dequeue: %d\n", dequeue(&queue)); // Should print 30
    printf("Dequeue: %d\n", dequeue(&queue)); // underflow

    return 0;
}