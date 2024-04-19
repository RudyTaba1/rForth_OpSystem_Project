#include <ctype.h>
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
	if(*token=='+'||*token=='-'||*token=='*'||*token=='/'){
       	parsedToken.TokenType = AR_OP;
       }
       	else if(*token==';'||*token==':'){
       	   parsedToken.TokenType = SYM;
       }
	   	else if(isdigit(*token)){
	   	   parsedToken.TokenType = NUMS;
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
  * 
 */
 /*void separate_token(int_stack_t *stk, char *txt, char* sList[], int sListVal[]){
	const char *space = " ";
	char *token;
	char *rest = txt;
	int top_stk;
	
	//this while loop will identify the operation via symbole and then do the operation
	while ((token = strtok_r(rest, space, &rest))){
		enum token_type_t type = parseToken(token).TokenType;
		int_stack_push(stk, atoi(token));
	

//		else if(type == AR_OP){
			
//			//can't do ops without at least 2 numbers
//			if(stk->size > 1){
//				if(strcmp(token, "+")==0){
//					int_stack_add(stk);
//				}
//				else if(strcmp(token, "-")==0){
//					int_stack_sub(stk);
//				}
//				else if(strcmp(token, "*")==0){
//					int_stack_mul(stk);
//				}
//				else if(strcmp(token, "/")==0){
//					int_stack_div(stk);
//				}
//				else if(strcmp(token, "mod")==0){
//					int_stack_mod(stk);
//				}
//				else if(strcmp(token, ".")==0){
//					int_stack_pop(stk, &top_stk);
//				}
//
//				else{
//					printf("Invalid operation\n");
//				}
//			}
//		}
		if(stk->size > 1){
		switch(type == AR_OP){
			case '+':
				int_stack_add(stk);
				break;
			case '-':
				int_stack_subtract(stk);
				break;
			case '*':
				int_stack_mult(stk);
				break;
			case '/':
				int_stack_div(stk);
				break;
			case 'mod':
				int_stack_mod(stk);
				break;
			case '.':
				int_stack_pop(stk, &top_stk);
				break;
			default:
				int_stack_push(stk, &top_stk);
				//printf("Stack Underflow\n");
				//int_stack_pop(stk, &top_stk);
		}
	}
		switch(type == WORDS){
			case'"dup':
				int_stack_dup(stk);
				break;
			case 'swap':
				int_stack_swap(stk);
				break;
			case 'over':
				int_stack_over(stk);
				break;
			case 'rot':
				int_stack_rot(stk);
				break;
			case 'var':
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

			default:
				printf("Stack Underflow\n");
				int_stack_pop(stk, &top_stk);
		}
		if(type==BOOLEAN){
			int_bool_integration(stk);
		}

 }
 }*/

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
	
	//this while loop will identify the operation via symbole and then do the operation
	while ((token = strtok_r(rest, space, &rest))){
		enum token_type_t type = parseToken(token).TokenType;
		
		
	//okay, now it works. 
	if(type == NUMS){
		int_stack_push(stk, atoi(token));
		}
	
	while(stk->size>4 && token != NULL){
		
		switch(type){
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
					int_stack_pop(stk, &top_stk);
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
				int_bool_integration(stk);
				break;
			default:
				printf("Stack Underflow\n");
				int_stack_pop(stk, &top_stk);
			}
		}	
	}
}
