//a test to make sure all the methods work
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "token.c"

int main(int argc, char *argv[]){
    //run here
char *testWord = "Hello";
tester(testWord, "Words", "Hello");

char *testNum = "123";
tester(testNum, "Numbers", "123");

char *testArOp = "+";
tester(testArOp, "Arithmetic Operations", "+");

char *testSym = ";";
tester(testSym, "Symboles", ";");
}

void tester(char *testcase, char *expectedType, char *expectedText){
    //tests spacelessToken
    TOKEN *token = SpacelessToken(testcase);
    //validates parsedToken
    while(token != NULL){
        TOKEN parsedToken = parseToken(token);
        //tests toString
        printf((toString(parsedToken.TokenType) == expectedType && parsedToken.txt == expectedText)
                   ? "Pass\n"
                   : "Fail\n");

        token = strtok(NULL, " ");
    }
    
}

