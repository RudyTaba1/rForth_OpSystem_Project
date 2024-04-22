#include <ctype.h>
#include <string.h>
#include "token.h"
#include "int_stack.c"
//comment test
/**
 * method inputs a String and removes the spaces
 * @return the token without spaces
 * */
char *SpacelessToken(char *input){
 	//initialized token
	char *token;
	//removes the spaces from the token
	token = strtok(input," ");
	return token;
 }//SpacelessToken()


/**
 * @returns type of token stored*/
char *toString(enum token_type_t TokenType){
	//switch will be easiest for this (God bless C)
	switch(TokenType){
		case NUMS:
		return "Numbers";
		case AR_OP:
		return "Arithmetic Operations";
		case SYM:
		return "Symboles";
		case WORDS:
		return "Words";
	default:
		return " ";
	}
 }//toString() method


/**
 * method parses the token and returns the type of token.
 * @return @param parsedToken.
*/
TOKEN parseToken(char *token){

   TOKEN parsedToken;
//checks if token is any of the structures
	if(*token=='+'||*token=='-'||*token=='*'||*token=='/'|| *token=='.'){
       	parsedToken.TokenType = AR_OP;
       }
       	else if(*token==';'||*token==':'){
       	   parsedToken.TokenType = SYM;
       }
	   	else if(isdigit(*token)){
	   	   parsedToken.TokenType = NUMS;
	   }
	   	else if(*token=='for'||*token=='if'||*token=='if-else'||*token=='do'){
			parsedToken.TokenType = LOOPS;
		}
	   	else if(*token=='>'||*token=='<'||strcmp(token, "and")==0||strcmp(token, "or")==0||strcmp(token, "invert")==0||*token == '='){
		   parsedToken.TokenType = BOOLEAN;
	   }
       else{
	       parsedToken.TokenType = WORDS;
       }
	//assigns the token to the parsedToken
   parsedToken.txt = token;
//returns the parsedToken
return parsedToken;       
 }

 
/**
 * rewrite of seperate token method.  Intended goal is to make the method load values onto the stack. For whatever reason, the previous method
 * does not do that. rather, takes the value and reads it, and then does not add it. rather, analyzes it, and give a stack underflow message.
 * 
*/
void separate_token(int_stack_t *stk, char *txt, char* sList[], int sListVal[]){
	const char *space = " ";
	char *token;
	char *rest = txt;
	int top_stk;
	enum token_type_t TokenType;
	
	//this while loop will identify the operation via symbole and then do the operation
	while ((token = strtok_r(rest, space, &rest))){
		enum token_type_t type = parseToken(token).TokenType;
		TokenType = type;
		
	//okay, now it works. 
	if(type == NUMS){
		int_stack_push(stk, atoi(token));
		}
	
	
	if(stk->size>0){
		
		switch(TokenType){
			case AR_OP:
				if(strcmp(token, "+")==0){
					int_stack_add(stk);
				}
				else if(strcmp(token, "-")==0){
					int_stack_subtract(stk);
				}
				else if(strcmp(token, "*")==0){
					int_stack_mult(stk);
				}
				else if(strcmp(token, "/")==0){
					int_stack_div(stk);
				}
				else if(strcmp(token, "mod")==0){
					int_stack_mod(stk);
				}
				else if(strcmp(token, ".")==0){
					int_stack_print(stk, stdout);
				}
				else{
					printf("Invalid operation\n");
				}
				break;
			case WORDS:
				if(strcmp(token, "dup")==0){
					int_stack_dup(stk);
				}
				else if(strcmp(token, "swap")==0){
					int_stack_swap(stk);
				}
				else if(strcmp(token, "over")==0){
					int_stack_over(stk);
				}
				else if(strcmp(token, "rot")==0){
					int_stack_rot(stk);
				}
				else if(strcmp(token, "pop")==0){
					int_stack_pop(stk, &top_stk);
				}
				else if(strcmp(token, "var")==0){
					token = strtok_r(NULL, space, &rest);
					if(token != NULL){
						for(int i = 0; i < 10; i++){
							if(sList[i] == NULL){
								sList[i] = strdup(token);
								sListVal[i] = 0; 
								break;
							}
						}
					}else{
						for(int i = 0; i<10; i++){
							if(sList[i] != NULL && strcmp(sList[i], token) == 0){
								int_stack_push(stk, sListVal[i]);
								break;

							}
					
						}
					}
				}
				else{
					printf("Stack Underflow\n");
					int_stack_pop(stk, &top_stk);
				}
				break;
			case BOOLEAN:
				if(strcmp(token, "and")==0){
					int_bool_and(stk);
				}
				else if(strcmp(token, "or")==0){
					int_bool_or(stk);
				}
				else if(strcmp(token, "invert")==0){
					int_bool_invert(stk);
				}
				else if(strcmp(token, ">")==0){
					int_bool_greater(stk);
				}
				else if(strcmp(token, "<")==0){
					int_bool_less(stk);
				}
				else if(strcmp(token, "=")==0){
					int_bool_equal(stk);
				}
				else{
					printf("Stack Underflow\n");
					int_stack_pop(stk, &top_stk);
					
				}
				break;
			default:
				break;
			}
		}	
	}
}
