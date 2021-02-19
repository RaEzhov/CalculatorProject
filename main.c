#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <complex.h>
//#include "tree.h"
#include <math.h>
#include "linkedList.h"
#include "variableList.h"

#define numberOfStrings 15
#define expressionLength 100
#define nameOfVariable 15
#define countOfAvailableFunctions 11
struct data {
    char* input[numberOfStrings];
    int top;
};

static char* availableFunctions[countOfAvailableFunctions] = {       "sin",  "cos",  "tan",  "atan", "log",  "lg",   "ln",   "sqrt", "pow",  "abs", "exp"};  // "-"
static char* availableFunctionsSymbols[countOfAvailableFunctions] ={ "!",    "@",    "#",    "№",    "$",    "%",    "&",    "?",    "_",    ":",   "\\"}; // "~"

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
    int strlenWhat = (int)strlen(what);
    int strlenForWhat = (int)strlen(forWhat);
    int strlenString = (int)strlen(string);
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
        // здесь я понял что ты не обработала дробные числа и сам написал какую то дичь временную чтобы оно работало)
        if (expression[i] == '.'){
            expressionWithSpaces[counterForSpaces - 1] = '.';
        }
        // конец моего кода)
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
        } else if(expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^' || expression[i] == ')' || expression[i] == '(' ){
            expressionWithSpaces[counterForSpaces++] = expression[i];
            counterForSpaces++;
        }
    }
    // ещё один костыль ибо в конце строки очень много пробелов, а должен быть хоть один /0
    for(int i = (int)strlen(expressionWithSpaces) - 1; expressionWithSpaces[i] == 32; i--){
        expressionWithSpaces[i] = 0;
    }
    //---------------
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
    while (expression) {
        switch (expression->status) {
            case 1:
                if (stackOperations) {
                    char sign;
                    if (stackOperations->status == 1){
                        sign = stackOperations->sign;
                    } else {
                        sign = stackOperations->bracket;
                    }
                    if (priority(sign) < priority(expression->sign)) {
                        pushToStack(&stackOperations, *expression);
                    } else {
                        while (priority(sign) >= priority(expression->sign) && stackOperations) {
                            pushToStack(&stackResult, popFromStack(&stackOperations));
                            if (stackOperations->status == 1){
                                sign = stackOperations->sign;
                            } else {
                                sign = stackOperations->bracket;
                            }
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
                break;
            default:
                exit(-7);
        }
        expression = expression->pointer;
    }
    return stackResult;
}

void clean(struct data input) {
    for (int i = 0; i <= input.top; i++) {
        free(input.input[i]);
    }
}

/*char whatIsIt(char* value){
    if(value[0] == )
}*/

EXPNODE* makeListFromExpression(char* expression, VARNODE* variables) {
    EXPNODE *list = NULL;
    char tempStr[expressionLength] = {0};
    while (strlen(expression)) {
        sscanf(expression, "%s ", tempStr);
        printf("%s\n", tempStr);
        expression = expression + strlen(tempStr) + 1;
        if (tempStr[0] == '+' || tempStr[0] == '-' || tempStr[0] == '*' || tempStr[0] == '/' || tempStr[0] == '^') {
            addToList(&list, 1, tempStr);
            continue;
        } else if (tempStr[0] >= '0' && tempStr[0] <= '9') {
            addToList(&list, 2, tempStr);
            continue;
        } else if (tempStr[0] == '(' || tempStr[0] == ')') {
            addToList(&list, 3, tempStr);
            continue;
        } else if (tempStr[0] >= 'a' && tempStr[0] <= 'z' || tempStr[0] >= 'A' && tempStr[0] <= 'Z') {
            char* doubleToStr = (char*)malloc(sizeof(char) * expressionLength);
            sprintf(doubleToStr, "%lf", retValue(variables,tempStr));
            addToList(&list,2,doubleToStr);
            free(doubleToStr);
            continue;
        } else {
            for(int i = 0; i < countOfAvailableFunctions; i++){
                if (!strcmp(tempStr,availableFunctionsSymbols[i])){
                    addToList(&list, 4, tempStr);
                    i = countOfAvailableFunctions;
                }
            }
            if (!strcmp(tempStr,"~")){
                addToList(&list,4,tempStr);
            }

        }
    }
    return list;
}

void initConstants(VARNODE** variables){
    addToVariableList(variables,"PI", M_PI);
    addToVariableList(variables, "E", M_E);
}

int main() {
    FILE *data = fopen("data.txt", "r");
    struct data inputData = {{0}, 0};

    inputData.top = fileReading(data, inputData.input);
    int counter = inputData.top;

    char variableTime[nameOfVariable] = {0};
    char expressionTime[expressionLength] = {0};

    VARNODE *variables = NULL;
    initConstants(&variables);
    EXPNODE *expressionList = NULL;
    EXPNODE *stackResult = NULL;
    for (int i = counter; i > 0; i--) {
        sscanf(inputData.input[i], "%s = %s", variableTime, expressionTime);
        strPrepare(expressionTime);
        expressionList = makeListFromExpression(expressionTime, variables); //make expression list from expressionTime // replace variables with their values
        stackResult = rpn(expressionList); //call rpn with expression list
        //call makeTree with stackResult from rpn
        //call treeCalculate with tree
        //push variable with treeCalculate result
        clearList(expressionList);
    }
    //calculate expression in input[0]
    clearVarList(variables);
    clearList(expressionList);
    fclose(data);
    clean(inputData);
    return 0;
}