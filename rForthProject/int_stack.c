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
        printf("\t ok");
        printf("\n"); 
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
        printf("popped value: %d\n", value);
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
    if (stk->size < 2){
        return 0;
    }
    
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int add = top_value + next_to_top_value;
    return int_stack_push(stk, add);
    
}

void int_stack_print(int_stack_t *stk, FILE *file) {
    int_entry_t *entry;
    int elements[stk->size]; 
    int i = 0;
    int pos = 0;
    if (stk->size == 0) {
        printf("empty stack\n");
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        if (i < stk->size) { 
            elements[i++] = entry->value;
        }
    }

    
    printf("Stack [%d]: ", stk->size);
    for (i = stk->size - 1; i >= 0; i--) {
        printf("%d ", elements[i]);
    }
    printf("<- Top\n");
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


int int_bool_and(int_stack_t *stk){
    int top_value, second_val;
    
        int_stack_pop(stk, &top_value);
        int_stack_pop(stk, &second_val);
        int and = top_value && second_val;
    
    return int_stack_push(stk, and);
    }

int int_bool_less(int_stack_t *stk){
    int top_value, second_val;
    
        int_stack_pop(stk, &top_value);
        int_stack_pop(stk, &second_val);
        int or = second_val < top_value;
    
    return int_stack_push(stk, or);
    }


int int_bool_greater(int_stack_t *stk){
    int top_value, second_val;
    
        int_stack_pop(stk, &top_value);
        int_stack_pop(stk, &second_val);
        int greater = (second_val > top_value);
    
    return int_stack_push(stk, greater);
    }


int int_bool_equal(int_stack_t *stk){
    int top_value, second_val;
    
        int_stack_pop(stk, &top_value);
        int_stack_pop(stk, &second_val);
        int equal = (second_val == top_value);
    
    return int_stack_push(stk, equal);
}

int int_bool_or(int_stack_t *stk){
    int top_value, second_val;
    
        int_stack_pop(stk, &top_value);
        int_stack_pop(stk, &second_val);
        int or = (top_value || second_val);
    
    return int_stack_push(stk, or);
}

int int_bool_invert(int_stack_t *stk){
    int top_val;
    int invert;

    int_stack_pop(stk, &top_val);
    
    if(top_val == 1){
           invert = 0;
    }
    
    if (top_val == 0){
          invert = 1;
     }
       
    return int_stack_push(stk, invert);

}
void int_var_init(var_store *store, int cap){
    for(int i = 0; i < cap; i++){
        store[i].key = NULL;
        store[i].value = 0;
    }
}

void int_var_store(var_store *store, int size, char *key, int value){
    if (store == NULL || key == NULL) {
        int_var_init(store, size);
        //fprintf(stderr, "Null pointer error\n");
        //return;
    }

    for(int i = 0; i < size; i++){
        if(store[i].key == NULL){
            store[i].key = strdup(key);
            store[i].value = value;
            break;
        }
    }
}

int int_isVar(var_store *store, char *key){
    for(int i = 0; i < 10; i++){
        if(store[i].key != NULL && strcmp(store[i].key, key) == 0){
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

int int_pushVar(int_stack_t *stk, var_store *store, char *key){
    for(int i = 0; i < 10; i++){
        if(store[i].key != NULL && strcmp(store[i].key, key) == 0){
            return int_stack_push(stk, store[i].value);
        }
    }
    return EXIT_FAILURE;
}