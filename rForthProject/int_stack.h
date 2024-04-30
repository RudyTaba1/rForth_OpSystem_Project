#ifndef INT_STACK_H
#define INT_STACK_H

#include <stdio.h>
#include <sys/queue.h>

#define __USE_GNU
#define _GNU_SOURCE

#include <search.h>
typedef struct int_entry {
    int value;
    SLIST_ENTRY(int_entry) entries;
} int_entry_t;

typedef struct int_stack {
    SLIST_HEAD(stackhead, int_entry) head;
    int size;
    int capacity;
} int_stack_t;

typedef struct wordentry {
    int value;
    char *key;
} wordentry;

typedef struct _word_table{
    #include <search.h>
    struct hsearch_data wtable;
    int values;
}wordtable;


extern void int_stack_init(int_stack_t *stk, int capacity);
extern int int_stack_push(int_stack_t *stk, int value);
extern int int_stack_pop(int_stack_t *stk, int *top_value);
extern int int_stack_top(int_stack_t *stk, int *top_value);
extern int int_stack_dup(int_stack_t *stk);
extern int int_stack_swap(int_stack_t *stk);
extern int int_stack_add(int_stack_t *stk);
extern void int_stack_print(int_stack_t *stk, FILE *file);
extern int int_stack_size(int_stack_t* stk);
extern int int_stack_capacity(int_stack_t* stk);
extern int int_stack_subtract(int_stack_t *stk);
extern int int_stack_mult(int_stack_t *stk);
extern int int_stack_div(int_stack_t *stk);
extern int int_stack_over(int_stack_t *stk);
extern int int_stack_rot(int_stack_t *stk);
extern int int_stack_2swap(int_stack_t *stk);
extern int int_stack_2dup(int_stack_t *stk);
extern int int_stack_2over(int_stack_t *stk);
extern int int_stack_mod(int_stack_t *stk);
extern int int_stack_divmod(int_stack_t *stk);
extern int int_bool_and(int_stack_t *stk);
extern int int_bool_less(int_stack_t *stk);
extern int int_bool_greater(int_stack_t *stk);
extern int int_bool_equal(int_stack_t *stk);
extern int int_bool_or(int_stack_t *stk);
extern int int_bool_invert(int_stack_t *stk);
//hashmap functions.
//initializes the hashmap
extern void int_var_init(wordtable *store, int cap);
//stores variable with val in hm
extern wordentry*  int_var_store(wordtable *store, int size, char *key, int value);
//checks to see if key is in hm
extern int int_isVar(wordtable *store, char *key);
//pushes the value of key to the stack
extern int int_pushVar(int_stack_t *stk, wordtable *store, char *key);
//different search function defined as wordentry
extern wordentry* int_searchVar(wordtable *store, char *key);


extern void separate_token(int_stack_t *stk, char *line, char *sList[], int sValues[]);

#endif // INT_STACK_H

