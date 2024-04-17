// int_stack.c

#include "int_stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/queue.h>

void int_stack_init(int_stack_t *stk, int capacity) {
    SLIST_INIT(&stk->head);
    stk->size = 0;
    stk->capacity = capacity;
}

int int_stack_push(int_stack_t *stk, int value) {
    if (stk->size >= stk->capacity) {
        printf("Stack is at full capacity.\n");
        return 0; // fail
    }

    int_entry_t *newEntry = malloc(sizeof(int_entry_t));
    if (newEntry) {
        newEntry->value = value; 
        SLIST_INSERT_HEAD(&stk->head, newEntry, entries);
        stk->size++;
        return 1; //success
    }
    return 0; // fail
}

int int_stack_pop(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        int value = entry->value;
        SLIST_REMOVE_HEAD(&stk->head, entries);
        free(entry);
        stk->size--;
        *top_value = value;
        return 1; // success
    }
    return 0; // fail
}

int int_stack_top(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        *top_value = entry->value;
        return 1; // success
    }
    return 0; // fail
}

/* Functions for FORTH langauge stack operators */

int int_stack_dup(int_stack_t *stk) {
    if (stk->size < 1)
        return 0;
    int top_value;
    int_stack_top(stk, &top_value);
    return int_stack_push(stk, top_value); // success only if last operation succeeds
}

int int_stack_swap(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value); // success only if last operation succeeds
}

/* Example of how to create a binary operator that works o top two elements (if present) */

int int_stack_add(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int add = top_value + next_to_top_value;
    return int_stack_push(stk, add);
}

void int_stack_print(int_stack_t *stk, FILE *file) {
    int_entry_t *entry;
    int pos = 0;
    if (stk->size == 0) {
        fprintf(file, "empty stack\n");
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        fprintf(file, "%d: %d\n", pos, entry->value);
        pos++;
    }
    printf("\n");
}

int int_stack_size(int_stack_t* stk) {
    return stk->size;
}

int int_stack_capacity(int_stack_t* stk) {
    return stk->capacity;
}

int int_stack_subtract(int_stack_t *stk) {
    //if there is only one element in the stack, return success (can't subtract one element)
    if (stk->size < 2){
        return EXIT_SUCCESS;
        }
    //top_value is the top element of the stack
    //second_stack_value is the second element of the stack
    int top_value, second_stack_value;
    //pop the top element of the stack and store it in top_value
    //this is asembly, I find this awesome
    int_stack_pop(stk, &top_value);
    //pop the top element of the stack and store it in second_stack_value
    int_stack_pop(stk, &second_stack_value);
    //push the difference of the two elements back onto the top of the stack
    int sub = second_stack_value - top_value;
    return int_stack_push(stk, sub);
}

int int_stack_mult(int_stack_t *stk) {
    //if there is only one element in the stack, return success (can't multiply one element)
    if (stk->size < 2){
        return EXIT_SUCCESS;
        }
    //repeat process of all arithmetic operations
    int top_value, second_stack_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_stack_value);
    //push value onto the stack
    int mult = second_stack_value * top_value;
    return int_stack_push(stk, mult);
}

int int_stack_div(int_stack_t *stk) {
    //if there is only one element in the stack, return success (can't divide one element)
    if (stk->size < 2){
        return EXIT_SUCCESS;
        }
    //repeat process of all arithmetic operations
    int top_value, second_stack_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_stack_value);
    int div = second_stack_value / top_value;
    //push value onto the stack
    return int_stack_push(stk, div);
}

int int_stack_over(int_stack_t *stk){
    if(stk->size < 2){
        return EXIT_SUCCESS;
        }
    int top_value, second_stack_value;
    //pop the top element of the stack and store it in top_value
    int_stack_pop(stk, &top_value);
    //pop the top element of the stack and store it in second_stack_value
    int_stack_pop(stk, &second_stack_value);
    //push the second_stack_value back onto the stack
    int_stack_push(stk, second_stack_value);
    //push the top_value back onto the stack
    int_stack_push(stk, top_value);

    return int_stack_push(stk, second_stack_value);
}
/**
 * This takes the top three elements of the stack, and pushes the third element top the top of the stack.
*/
int int_stack_rot(int_stack_t *stk){
    if(stk->size < 2){
        return EXIT_SUCCESS;
        }
    int top_value, second_stack_value, third_stack_value;
    //initializes top of the stack
    int_stack_pop(stk, &top_value);
    //pops top of the stack to second value
    int_stack_pop(stk, &second_stack_value);
    //pops top of stack into third value
    int_stack_pop(stk, &third_stack_value);
    //pushes second value to top of stack
    int_stack_push(stk, second_stack_value);
    //pushes the third value to the top of the stack
    int_stack_push(stk, top_value);
    //returns the third stack value at the top of the stack
    return int_stack_push(stk, third_stack_value);
}
int int_stack_2swap(int_stack_t *stk){
    if(stk->size < 4){
        return EXIT_SUCCESS;
        }
    int top_value, second_stack_value, third_stack_value, fourth_stack_value;
    //initializes top of the stack
    int_stack_pop(stk, &top_value);
    //pops top of the stack to second value
    int_stack_pop(stk, &second_stack_value);
    //pops top of stack into third value
    int_stack_pop(stk, &third_stack_value);
    //pops top of stack into fourth value
    int_stack_pop(stk, &fourth_stack_value);
    //pushes second value to top of stack
    int_stack_push(stk, second_stack_value);
    //pushes the third value to the top of the stack
    int_stack_push(stk, top_value);
    //pushes the fourth value to the top of the stack
    int_stack_push(stk, third_stack_value);
    //pushes the top value to the top of the stack
    return int_stack_push(stk, fourth_stack_value);
}
/**
 * This takes the top two elements of the stack, and pushes the second element to the top of the stack.
*/
int int_stack_2dup(int_stack_t *stk){
    if(stk->size < 2){
        return EXIT_SUCCESS;
        }
    int top_value, second_stack_value;
    //pop the top element of the stack and store it in top_value
    int_stack_pop(stk, &top_value);
    //pop the top element of the stack and store it in second_stack_value
    int_stack_pop(stk, &second_stack_value);
    //push the second_stack_value back onto the stack
    int_stack_push(stk, second_stack_value);
    //push the top_value back onto the stack
    int_stack_push(stk, top_value);
    //push the second_stack_value back onto the stack
    return int_stack_push(stk, second_stack_value);
}

int int_stack_2over(int_stack_t *stk){
    if(stk->size < 2){
        return EXIT_SUCCESS;
        }
    int top_value, second_stack_value, third_stack_value, fourth_stack_value;
    //initializes top of the stack
    int_stack_pop(stk, &top_value);
    //pops top of the stack to second value
    int_stack_pop(stk, &second_stack_value);
    //pops top of stack into third value
    int_stack_pop(stk, &third_stack_value);
    //pops top of stack into fourth value
    int_stack_pop(stk, &fourth_stack_value);
    //pushes the third value to the top of the stack
    int_stack_push(stk, third_stack_value);
    //pushes the fourth value to the top of the stack
    int_stack_push(stk, second_stack_value);
    //pushes the top value to the top of the stack
    return int_stack_push(stk, top_value);
}

int int_stack_mod(int_stack_t *stk){
    //uses the same process as all other arithmetic operations
    if(stk->size < 2){
        return EXIT_SUCCESS;
        }
    int top_value, second_stack_value;
    //pop the top element of the stack and store it in top_value
    int_stack_pop(stk, &top_value);
    //pop the top element of the stack and store it in second_stack_value
    int_stack_pop(stk, &second_stack_value);
    //push the second_stack_value back onto the stack
    int_stack_push(stk, second_stack_value);
    //push the top_value back onto the stack
    int_stack_push(stk, top_value);
    //push the second_stack_value back onto the stack
    return int_stack_push(stk, second_stack_value % top_value);
}

int int_stack_divmod(int_stack_t *stk){
    if(stk->size<2){
        return EXIT_SUCCESS;
        }
    //init variables
    int top_value, second_stack_value, remainder, quotient;
    //makes life easier
    remainder = second_stack_value % top_value;
    quotient = second_stack_value / top_value;

    //define values of vars
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_stack_value);
    //push the quotient, return remainder
    int_stack_push(stk, quotient);
    return int_stack_push(stk, remainder);
}


int int_bool_integration(int_stack_t *stk){
    int top_value, second_stack_value;
    char bool_op;
    if(stk->size<2){
        int_stack_pop(stk, &top_value);
        int_stack_pop(stk, &second_stack_value);
        int_stack_pop(stk, &bool_op);
        if(bool_op == '&'){
            return int_stack_push(stk, top_value && second_stack_value);
            }
        else if(bool_op == '|'){
            return int_stack_push(stk, top_value || second_stack_value);
            }
        else if(bool_op == '!'){
            return int_stack_push(stk, !top_value);
            }
        else if(bool_op == '<'){
            return int_stack_push(stk, top_value < second_stack_value);
            }
        else if(bool_op == '>'){
            return int_stack_push(stk, top_value > second_stack_value);
            }
        else if(bool_op == '='){
            return int_stack_push(stk, top_value == second_stack_value);
        }
        else{
            return EXIT_FAILURE;
            }
        }
    }


