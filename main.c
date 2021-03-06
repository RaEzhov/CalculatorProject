#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
                        while ( stackOperations && priority(sign) >= priority(expression->sign)) {
                            pushToStack(&stackResult, popFromStack(&stackOperations));
                            if (stackOperations) {
                                if (stackOperations->status == 1) {
                                    sign = stackOperations->sign;
                                } else {
                                    sign = stackOperations->bracket;
                                }
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

BRANCH* makeTree(EXPNODE** topStackResult){
    BRANCH * root = NULL;
    while (*topStackResult){
        EXPNODE expTemp = popFromStack(topStackResult);
        BRANCH temp = {expTemp.status, expTemp.sign, expTemp.number, expTemp.function, NULL, NULL, NULL};
        while (temp.status == 0){
            while(root->status != 4){
                root = root->parent;
            }
            if ((*root).parent){
                root = root->parent;
            }
            if (!(*topStackResult)){
                return root;
            }
            expTemp = popFromStack(topStackResult);
            temp.status = expTemp.status;
            temp.sign = expTemp.sign;
            temp.number = expTemp.number;
            temp.function = expTemp.function;
        }
        addToTree(&root,temp);
    }
    return root;
}

double calculateSymbol(double left, double right, char status, char action){
    if(status == 1) {
        switch (action) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                if (right == 0)
                    exit(-20);
                return left / right;
            case '^':
                return pow(left, right);
            default:
                exit(-10);
        }
    }
    if(status == 4){
        switch (action){
            case '!':
                return sin(right);
            case '@':
                return cos(right);
            case '#':
                return tan(right);
            case '|':
                return atan(right);
            case '$':
                return log2(right);
            case '%':
                return log10(right);
            case '&':
                return log(right);
            case '?':
                return sqrt(right);
            case '_':
                return round(right);
            case ':':
                return fabs(right);
            case '\\':
                return exp(right);
            case '~':
                return (-right);
            default:
                exit(-10);
        }
    }
    exit(-10);
}

double treeCalculate(BRANCH* tree){
    if (tree->status == 4) {
        if (tree->right->status != 2) {
            treeCalculate(tree->right);
        }
        tree->number = calculateSymbol(0, tree->right->number, 4, tree->function);
        tree->status = 2;
        free(tree->right);
        tree->right = NULL;
    }
    if (tree->status == 1){
        if (tree->right->status != 2){
            treeCalculate(tree->right);
        }
        if (tree->left->status != 2){
            treeCalculate(tree->left);
        }
        tree->number = calculateSymbol(tree->left->number, tree->right->number, 1, tree->sign);
        tree->status = 2;
        free(tree->right);
        free(tree->left);
        tree->right = NULL;
        tree->left = NULL;
    }
    if (tree->parent == NULL && tree->status == 2) {
        return tree->number;
    }
}

int main() {
    FILE *data = fopen("data.txt", "r");

    struct data inputData = {{0}, 0};

    inputData.top = fileReading(data, inputData.input);
    int counter = inputData.top;

    char variableTime[nameOfVariable] = {0};
    char expressionTime[expressionLength] = {0};

    VARNODE* variables = NULL;
    initConstants(&variables);
    EXPNODE* expressionList = NULL;
    EXPNODE* stackResult = NULL;
    BRANCH* tree = NULL;
    double resultValue = 0;
    for (int i = counter; i >= 0; i--) {
        if( i > 0) {
            sscanf(inputData.input[i], "%s = ", variableTime);
            strcpy(expressionTime, inputData.input[i] + strlen(variableTime) + 3);
        } else {
            strcpy(expressionTime, inputData.input[i]);
        }
        strPrepare(expressionTime);
        expressionList = makeListFromExpression(expressionTime, variables); //make expression list from expressionTime // replace variables with their values
        stackResult = rpn(expressionList); //call rpn with expression list
        tree = makeTree(&stackResult);//call makeTree with stackResult from rpn
        while(tree->parent){
            tree = tree->parent;
        }
        resultValue = treeCalculate(tree);//call treeCalculate with tree
        addToVariableList(&variables,variableTime,resultValue);//push variable with treeCalculate result
        clearList(stackResult);
        stackResult = NULL;
        clearList(expressionList);
        expressionList = NULL;
        strclear(expressionTime);
        strclear(variableTime);
        deleteTree(tree);
    }
    printf("Expression value: %.2lf\n", resultValue);
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