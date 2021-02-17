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

/*typedef struct variable {
    char name[numberOfStrings];
    double value;
    struct variable* pointer;
}NODE;*/

void strclear(char str[]){
    int i = 0;
    while(str[i]){
        str[i] = 0;
        i++;
    }
}

/*void addToList(char* nameCur, double valueCur, NODE** tail) {
    NODE* current = NULL;
    current = (NODE*)malloc(sizeof(NODE));
    strcpy(current->name, nameCur);
    current->value = valueCur;
    current->pointer = NULL;
    (**tail).pointer = current;
    *tail = current;
}*/

void strReplace(char* string, char what[], char forWhat[], int sizeOfString){
    int pos = 0;
    for(int i = 0; i < strlen(string) - strlen(what); i++){
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

void addSpaces(char* expression, char* expressionWithSpaces){
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

void clean(char* input[], int size) {
    for (int i = 0; i <= size; i++) {
        free(input[i]);
    }
}

int main() {

    char a[] = "Hello, world!";
    printf("%s\nWhat's your name?\n", a);
    char name[20] = {0};
    scanf("%s", name);
    strReplace(a,"world", name,20);
    printf("%s\n", a);

    EXPNODE* stack = NULL;
    pushToStack(&stack,3, "(");
    pushToStack(&stack,2, "214");
    pushToStack(&stack,1, "*");
    pushToStack(&stack,3, "(");
    pushToStack(&stack,2, "214");
    pushToStack(&stack,1, "*");
    popFromStack(&stack);
    popFromStack(&stack);
    popFromStack(&stack);
    popFromStack(&stack);
    popFromStack(&stack);
    popFromStack(&stack);

    EXPNODE * expList = NULL;
    addToList(&expList,1,"-");
    addToList(&expList,2,"324.41");
    addToList(&expList,3,")");
    clearList(expList);

    VARNODE * list = NULL;
    addToVariableList(&list,"PI",3.14);
    addToVariableList(&list,"e", 2.7);
    double pi = retValue(list,"PI");
    clearVarList(list);

    /*FILE* data = fopen("data.txt", "r");
    struct data inputData = { {0}, 0 };
    char* input[numberOfStrings] = { 0 };
    int top = fileReading(data, input);
    int counter = 0;
    counter = top;

    char variableTime[nameOfVariable] = {0};
    char expressionTime[expressionLength] = {0};

    for (int i = counter; i < 0; i--){
        sscanf(input[i],"%s = %s", variableTime, expressionTime);

    }

    char exp[100] = {0};
    char exps[200] = {0};
    for(int i = 0; i <= 200; i++){
        exps[i] = 32;
    }
    scanf("%s", exp);
    addSpaces(exp, exps);
    printf("%s", exps);

    for (int i = 0; i < strlen(exps); i++){

    }

    fclose(data);
    clean(input, top);
*/
    return 0;
}
