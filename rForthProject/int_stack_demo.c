
#include "int_stack.h"
#include "int_stack.c"

#include <stdlib.h>
#include <stdio.h>


int main() {
    int_stack_t myStack;
    const int capacity = 5;

    // Initialize the stack with a capacity of 5.
    int_stack_init(&myStack, capacity);

    // Push values onto the stack.
    for (int i = 0; i < capacity; i++) {
        int success = int_stack_push(&myStack, i);
        if (!success) {
            fprintf(stderr, "Stack overflow: %d\n", i);
        }
    }

    // Print the stack (top to bottom)
    int_stack_print(&myStack, stdout);

    // Pop values from the stack and print them.
    for (int i = 0; i < capacity; i++) {
        int top_value;
        int success = int_stack_pop(&myStack, &top_value);
        if (!success) {
            fprintf(stderr, "Stack empty\n");
        }
    }

    // Print the stack (top to bottom)
    int_stack_print(&myStack, stdout);

    // Quick tests for swap, dup, and add.

    int_stack_push(&myStack, 7);
    int_stack_push(&myStack, 8);
    int_stack_print(&myStack, stdout);
    int_stack_swap(&myStack);
    int_stack_print(&myStack, stdout);
    int_stack_add(&myStack);
    int_stack_print(&myStack, stdout); // hopefully, 15 only item on stack!
    int_stack_dup(&myStack);
    int_stack_print(&myStack, stdout); // hopefully, 15 only item on stack!
    int_stack_add(&myStack);
    int_stack_print(&myStack, stdout); // hopefully, 30 only item on stack!

    // Test for over, rot, 2dup, 2over, 2swap, subtract, mult, div, mod, divmod
    int_stack_push(&myStack, 7);
    int_stack_push(&myStack, 8);
    int_stack_push(&myStack, 9);
    int_stack_push(&myStack, 10);
    int_stack_push(&myStack, 11);
    int_stack_print(&myStack, stdout);
    int_stack_over(&myStack);
    int_stack_print(&myStack, stdout); // should have 11, 10, 9, 8, 7, 11
    int_stack_rot(&myStack);
    int_stack_print(&myStack, stdout); // should have 11, 10, 9, 7, 8, 11
    int_stack_2dup(&myStack);
    int_stack_print(&myStack, stdout); // should have 11, 10, 9, 7, 8, 11, 8, 11
    int_stack_2over(&myStack);
    int_stack_print(&myStack, stdout); // should have 11, 10, 9, 7, 8, 11, 8, 11, 10, 9
    int_stack_2swap(&myStack);
    int_stack_print(&myStack, stdout); // should have 11, 10, 9, 7, 8, 11, 10, 9, 8, 11
    int_stack_subtract(&myStack);
    int_stack_print(&myStack, stdout); // should have 11, 10, 9, 7, 3
    int_stack_mult(&myStack);
    int_stack_print(&myStack, stdout); // should have 11, 10, 9, 21
    int_stack_div(&myStack);
    int_stack_print(&myStack, stdout); // should have 11, 10, 2
    int_stack_mod(&myStack);
    int_stack_print(&myStack, stdout); // should have 11, 0
    int_stack_divmod(&myStack);
    int_stack_print(&myStack, stdout); // should have 0, 11
    
    return 0;
}

