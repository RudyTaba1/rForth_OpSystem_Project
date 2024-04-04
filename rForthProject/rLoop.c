#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.c"
int main(int argc, char *argv[]){

printf("Welcome to rForth! Type 'bye' to exit. \n");

char* input = malloc(100);
//stack
int_stack_t stk;
//read for line
char *line = NULL;
//len of line is zero at beginning
size_t len = 0;
//reads line
ssize_t read;
//String list for var
char *sList[100];
//Variable values at String List
int sValues[100];

//initialize stack
int_stack_init(&stk, 100);
for(int i = 0; i<100; i++){
    sList[i] = NULL;
    sValues[i] = 0;
}

/**
 * From here, I will attempt to build the for loop that houses the interpreter. I don't really know how to go about it, but I'll give it a shot.
*/


}