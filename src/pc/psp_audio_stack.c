#if defined(TARGET_PSP)
#include <stdio.h>

#include "psp_audio_stack.h"

/* Basic stack, fixed size */
static struct Stack {
    int top;
    int capacity;
    //int *array;
    AudioTask array[14];
} _stack __attribute__((aligned(32)));

/* return the Only stack, with fixed size */
struct Stack *createStack(unsigned capacity) {
    (void) capacity;
    struct Stack *stack = &_stack;
    stack->capacity = 14;
    stack->top = -1;
    return stack;
}

int stack_isFull(struct Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int stack_isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

void stack_push(struct Stack *stack, AudioTask item) {
    if (stack_isFull(stack))
        return;
    /* Possible uncached way, not sure we need */
    //++stack->top;
    //AudioTask *index = (AudioTask *)((size_t)(stack->array + stack->top) | 0x40000000 );
    //*index = item;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
AudioTask stack_pop(struct Stack *stack) {
    return stack_isEmpty(stack) ? NOP : stack->array[stack->top--];
}

AudioTask stack_peek(struct Stack *stack) {
    return stack_isEmpty(stack) ? NOP : stack->array[stack->top];
}

void stack_clear(struct Stack *stack) {
    stack->top = -1;
}
#endif
