#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <complex.h>
#include "tree.h"
#include <math.h>
#include "linkedList.h"
#include "variableList.h"

#define numberOfStrings 15
#define expressionLength 100
#define nameOfVariable 15

struct data {
    char* input[numberOfStrings];
    int top;
};

static char* availableFunctions[] = {       "sin",  "cos",  "tan",  "atan", "log",  "lg",   "ln",   "sqrt", "pow",  "abs", "exp"};  // "-"
static char* availableFunctionsSymbols[] ={ "!",    "@",    "#",    "№",    "$",    "%",    "&",    "?",    "_",    ":", (char*)1}; // "~"
static int countOfAvailableFunctions = 11;

void strclear(char str[]){
    int i = 0;
    while(str[i]){
        str[i] = 0;
        i++;
    }
}

int priority(char sign){
    switch (sign) {
    case '(': case ')':
        return 0;
    case '+': case '-':
        return 1;
    case '*': case '/':
        return 2;
    case '^':
        return 3;
    default:
        exit(-6);
    }
}

void strReplace(char* string, char what[], char forWhat[], int sizeOfString){
    int pos = 0;
    for(int i = 0; i < (strlen(string) - strlen(what)); i++){
        for(int j = 0; j < strlen(what); j++){
            if (string[j + i] != what[j]){
                i++;
                j = -1;
                continue;
            }
        }
        pos = i;
        break;
    }
    int strlenWhat = strlen(what);
    int strlenForWhat = strlen(forWhat);
    int strlenString = strlen(string);
    if(strlenWhat == strlenForWhat){
        int j = 0;
        for(int i = pos; i < pos + strlenWhat; i++){
            string[i] = forWhat[j++];
        }
        return;
    }
    if (strlenWhat > strlenForWhat){
        int j = 0;
        for(int i = pos; i < pos + strlenForWhat; i++){
            string[i] = forWhat[j++];
        }
        for(int i = pos + strlenForWhat; i < strlenString - (strlenWhat - strlenForWhat); i++){
            string[i] = string[i + strlenWhat - strlenForWhat];
        }
        for(int i =  strlenString - 1; i >= strlenString - (strlenWhat - strlenForWhat); i--){
            string[i] = 0;
        }
        return;
    }
    if (strlenWhat < strlenForWhat){
        if (strlenString + strlenForWhat - strlenWhat >= sizeOfString){
            exit(-5);
        }
        for(int i = strlenString + strlenForWhat - strlenWhat - 1; i >= pos; i--){
            string[i] = string[i-strlenForWhat + strlenWhat];
        }
        int j = 0;
        for(int i = pos; i < pos + strlenForWhat; i++){
            string[i] = forWhat[j++];
        }
    }
}

void addSpaces(char* expression){
    char expressionWithSpaces[expressionLength] = {0};
    for (int i = 0; i < expressionLength; i++){
        expressionWithSpaces[i] = 32;
    }
    int counterForTime = 0;
    int counterForSpaces = 0;
    char timeSymbols[nameOfVariable] = {0};
    for (int i = 0; i < strlen(expression); i++){
        if(expression[i] >= '0' && expression[i] <= '9'){
            timeSymbols[counterForTime++] = expression[i];
            while(expression[i+1] >= '0' && expression[i+1] <= '9'){
                timeSymbols[counterForTime++] = expression[i+1];
                i++;
            }
            for(int j = 0; j < counterForTime; j++){
                expressionWithSpaces[counterForSpaces++] = timeSymbols[j];
            }
            counterForSpaces++;
            counterForTime = 0;
            strclear(timeSymbols);
        } else if(expression[i] >= 'a' && expression[i] <= 'z' || expression[i] >= 'A' && expression[i] <= 'Z'){
            timeSymbols[counterForTime++] = expression[i];
            while(expression[i+1] >= 'a' && expression[i+1] <= 'z' || expression[i+1] >= 'A' && expression[i+1] <= 'Z' || expression[i+1] >= '0' && expression[i+1] <= '9'){
                timeSymbols[counterForTime++] = expression[i+1];
                i++;
            }
            for(int k = 0; k < counterForTime; k++){
                expressionWithSpaces[counterForSpaces++] = timeSymbols[k];
            }
            counterForSpaces++;
            counterForTime = 0;
            strclear(timeSymbols);
        } else if(expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^' || expression[i] == ')' || expression[i] == '('){
            expressionWithSpaces[counterForSpaces++] = expression[i];
            counterForSpaces++;
        }
    }
    strcpy(expression, expressionWithSpaces);
}

void strPrepare(char* expression){
    addSpaces(expression);
    for (int i = 0; i < countOfAvailableFunctions; i++){
        while (strstr(expression, availableFunctions[i])){
            strReplace(expression,availableFunctions[i],availableFunctionsSymbols[i], expressionLength);
        }
    }
    while (strstr(expression, "( -")){
        strReplace(expression,"( -","~ (", expressionLength);
    }
}

int fileReading(FILE* file, char* input[]) {
    int counter = 0;
    while (!feof(file)) {
        input[counter] = (char*)malloc(sizeof(char) * expressionLength);
        fgets(input[counter], expressionLength, file);
        if (input[counter][strlen(input[counter]) - 1] == '\n') {
            input[counter][strlen(input[counter]) - 1] = 0;
        }
        counter++;
    }
    return counter - 1;
}

EXPNODE* rpn(EXPNODE* expression) {
    EXPNODE *stackOperations = NULL;
    EXPNODE *stackResult = NULL;
    EXPNODE zeroSpace = {0, 0, 0, 0, 0, NULL};
    int functionCounter = 0;
    while (expression->pointer) {
        switch (expression->status) {
            case 1:
                if (stackOperations) {
                    if (priority(stackOperations->sign) < priority(expression->sign)) {
                        pushToStack(&stackOperations, *expression);
                    } else {
                        while (priority(stackOperations->sign) >= priority(expression->sign) && stackOperations) {
                            pushToStack(&stackResult, popFromStack(&stackOperations));
                        }
                        pushToStack(&stackOperations, *expression);
                    }
                }
                break;
            case 2:
                pushToStack(&stackResult, *expression);
                break;
            case 3:
                if (expression->bracket == '(') {
                    pushToStack(&stackOperations, *expression);
                } else {
                    while (stackOperations->status != 3 || stackOperations->bracket != '(') {
                        pushToStack(&stackResult, popFromStack(&stackOperations));
                    }
                    popFromStack(&stackOperations);
                    if (stackOperations->status == 4) {
                        pushToStack(&stackResult, popFromStack(&stackOperations));
                    }
                }
                break;
            case 4:
                pushToStack(&stackResult, zeroSpace);
                pushToStack(&stackOperations, *expression);
            default:
                exit(-7);
        }
    }
    return stackResult;
}

void clean(struct data input) {
    for (int i = 0; i <= input.top; i++) {
        free(input.input[i]);
    }
}

int main() {
    FILE* data = fopen("data.txt", "r");
    struct data inputData = { {0}, 0 };

    inputData.top = fileReading(data, inputData.input);
    int counter = 0;
    counter = inputData.top;

    char variableTime[nameOfVariable] = {0};
    char expressionTime[expressionLength] = {0};



   for (int i = counter; i < 0; i--){
        sscanf(inputData.input[i],"%s = %s", variableTime, expressionTime);
        strPrepare(expressionTime);
        //make expression list from expressionTime // replace variables with their values
        //call rpn with expression list
        //call makeTree with stackResult from rpn
        //call treeCalculate with tree
        //push variable with treeCalculate result
   }

   //calculate expression in input[0]


   fclose(data);
   clean(inputData);
    return 0;
}
