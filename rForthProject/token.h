//header file and definitions for token.c

//begin definitions
#ifndef TOKEN_H
#define TOKEN_H

//Differeent token types
enum token_type_t{
	NUMS,
	AR_OP,
	SYM,
	WORDS,
	BOOLEAN,
	LOOPS,
	VARS
  }TOKEN_TYPE;

//Token Structure
typedef struct token_t{
	//define token type
	enum token_type_t TokenType;
	//char pointer to token
	char *txt;
  } TOKEN;

//toString method to show Token type
char *toString(enum token_type_t TokenType);

//Generate a spaceless token
char *SpacelessToken(char *input);

//Parses the token. In other words, checks structure of Token
TOKEN parseToken(char *token);

//seperates the token


#endif
  //token.h
