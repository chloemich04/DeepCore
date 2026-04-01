#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top; // index of top element (-1 if stack is empty)
} Stack;

void init_stack(Stack* stack);
int is_stack_empty(Stack* stack);
int is_stack_full(Stack* stack);
void push(Stack* stack, int value);
int pop(Stack* stack);
int peek(Stack* stack);

#endif