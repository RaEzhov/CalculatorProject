#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <complex.h>
//#include "tree.h"
#include <math.h>
#include "linkedList.h"

#define numberOfStrings 15
#define expressionLength 100
#define nameOfVariable 15

struct data {
    char* input[numberOfStrings];
    int top;
};



typedef struct variable {
    char name[numberOfStrings];
    double value;
    struct variable* pointer;
}NODE;

void strclear(char str[]){
    int i = 0;
    while(str[i]){
        str[i] = 0;
        i++;
    }
}

void addToList(char* nameCur, double valueCur, NODE** tail) {
    NODE* current = NULL;
    current = (NODE*)malloc(sizeof(NODE));
    strcpy(current->name, nameCur);
    current->value = valueCur;
    current->pointer = NULL;
    (**tail).pointer = current;
    *tail = current;
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
    FILE* data = fopen("data.txt", "r");
    struct data inputData = { {0}, 0 };
    char* input[numberOfStrings] = { 0 };
    int top = fileReading(data, input);
    int counter = 0;
    counter = top;

    char variableTime[nameOfVariable] = {0};
    char expressionTime[expressionLength] = {0};

    /*for (int i = counter; i < 0; i--){
        sscanf(input[i],"%s = %s", variableTime, expressionTime);

    }*/

    char exp[100] = {0};
    char exps[200] = {0};
    for(int i = 0; i <= 200; i++){
        exps[i] = 32;
    }
    scanf("%s", exp);
    addSpaces(exp, exps);
    printf("%s", exps);


    NODE* tail = NULL;
    fclose(data);
    clean(input, top);
    return 0;
}
