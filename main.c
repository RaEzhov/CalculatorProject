#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "tree.h"
#include "linkedList.h"
#include "variableList.h"
#include "stringFunctions.h"

#define numberOfStrings 15

struct data {
    char* input[numberOfStrings];
    int top;
};

int fileReading(FILE* file, char* input[]);

void clean(struct data input);

void initConstants(VARNODE** variables);


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
                } else {
                    pushToStack(&stackOperations, *expression);
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
                    if (stackOperations && stackOperations->status == 4) {
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
    while (stackOperations) {
        pushToStack(&stackResult, popFromStack(&stackOperations));
    }
    return stackResult;
}

EXPNODE* makeListFromExpression(char* expression, VARNODE* variables) {
    EXPNODE *list = NULL;
    char tempStr[expressionLength] = {0};
    while (strlen(expression)) {
        sscanf(expression, "%s ", tempStr);
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

void printList(EXPNODE* list){
    while(list) {
        switch (list->status) {
            case 0:
                printf(" ");
                break;
            case 1:
                printf("%c", list->sign);
                break;
            case 2:
                printf("%.2lf",list->number);
                break;
            case 3:
                printf("%c", list->bracket);
                break;
            case 4:
                if (list->function == '~') {
                    printf("-");
                } else{
                    int i = 0;
                    while (list->function != availableFunctionsSymbols[i][0]){
                        i++;
                    }
                    printf("%s", availableFunctions[i]);
                }
                break;
            default:
                exit(-8);
        }
        list = list->pointer;
    }
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
        sscanf(inputData.input[i], "%s = ", variableTime);
        strcpy(expressionTime,inputData.input[i] + strlen(variableTime) + 3);
        strPrepare(expressionTime);
        expressionList = makeListFromExpression(expressionTime, variables); //make expression list from expressionTime // replace variables with their values
        stackResult = rpn(expressionList); //call rpn with expression list
        printList(stackResult);
        printf("\n");
        printList(expressionList);
        printf("\n");
        //call makeTree with stackResult from rpn
        //call treeCalculate with tree
        addToVariableList(&variables,variableTime,0);//push variable with treeCalculate result
        clearList(stackResult);
        stackResult = NULL;
        clearList(expressionList);
        expressionList = NULL;
        strclear(expressionTime);
        strclear(variableTime);
    }
    //calculate expression in input[0]
    clearVarList(variables);
    clearList(expressionList);
    fclose(data);
    clean(inputData);
    return 0;
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

void clean(struct data input) {
    for (int i = 0; i <= input.top; i++) {
        free(input.input[i]);
    }
}

void initConstants(VARNODE** variables){
    addToVariableList(variables,"PI", M_PI);
    addToVariableList(variables, "E", M_E);
}