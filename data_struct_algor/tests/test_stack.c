#include <stdio.h>
#include "stack.h"

int test_stack() {
    Stack stack;
    init_stack(&stack);

    printf("Testing Stack:\n");
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Peek: %d\n", peek(&stack)); // Should print 30
    printf("Pop: %d\n", pop(&stack)); // Should print 30
    printf("Pop: %d\n", pop(&stack)); // Should print 20
    printf("Peek: %d\n", peek(&stack)); // Should print 10
    printf("Pop: %d\n", pop(&stack)); // Should print 10
    printf("Pop: %d\n", pop(&stack)); // underflow
    
    return 0;
}