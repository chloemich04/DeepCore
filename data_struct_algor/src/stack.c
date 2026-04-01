#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/*
 * Initialize the stack
 @param stack = The stack to initialize
 */
void init_stack(Stack* stack) {
    stack->top = -1; // empty stack
}


/*
 * Check if the stack is empty
 @param stack = The stack to check
 */
int is_stack_empty(Stack* stack) {
    return stack->top == -1;
}

/*
 * Check if the stack is full
    @param stack = The stack to check
 */
int is_stack_full(Stack* stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

/*
 * Push an element onto the stack
    @param stack = The stack to push onto
    @param value = The value to push
 */
void push(Stack* stack, int value) {
    if (is_stack_full(stack)) {
        printf("Stack overflow!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

/*
 * Pop an element from the stack
    @param stack = The stack to pop from
 */
int pop(Stack* stack) {
    if(is_stack_empty(stack)) {
        printf("Stack overflow!\n");
        return -1;
    }
    return stack->data[stack->top--];
}

/*
 * Peek at the top element of the stack
    @param stack = The stack to peek at
 */
int peek(Stack* stack) {
    if (is_stack_empty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->data[stack->top];
}



