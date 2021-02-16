#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <complex.h>
//#include "tree.h"
#include <math.h>

#define numberOfStrings 15
#define expressionLength 100
#define nameOfVariable 15

struct data {
    char* input[numberOfStrings];
    int top;
};

typedef struct expressionNode{
    char status; //0 - not initialized 1 - sign 2 - number 3 - bracket
    char sign;
    double number;
    char bracket;
} EXPNODE;

typedef struct variable {
    char name[numberOfStrings];
    double value;
    struct variable* pointer;
}NODE;

void addToList(char* nameCur, double valueCur, NODE** tail) {
    NODE* current = NULL;
    current = (NODE*)malloc(sizeof(NODE));
    strcpy(current->name, nameCur);
    current->value = valueCur;
    current->pointer = NULL;
    (**tail).pointer = current;
    *tail = current;
}

void addSpaces(char* expression, char* expressionWithSpaces, ){
    for (int i = 0; i < strlen(expression); i++){
        if(expression[i])
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

    for (int i = counter; i < 0; i--){
        sscanf(input[i],"%s = %s", variableTime, expressionTime);

    }

    while (counter >= 0) {
        printf("%s\n", input[counter]);
        counter--;
    }
    NODE* tail = NULL;
    fclose(data);
    clean(input, top);
    return 0;
}
