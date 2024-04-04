//packages required to run main
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "token.c"

int main(int argc, char* argv[]){
//run here
	printf("Enter a token: ");
	scanf("%s",argv);
	char *token = SpacelessToken(argv);
	while(token != NULL){
		TOKEN parsedToken = parseToken(token);
		printf("Token: %s is of type: %s\n",parsedToken.txt,toString(parsedToken.TokenType));
		token = strtok(NULL," ");
	}
	return 0;
}
