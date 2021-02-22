#include "stringFunctions.h"
#include <string.h>
#include <stdlib.h>

void strclear(char str[]){
    int i = 0;
    while(str[i]){
        str[i] = 0;
        i++;
    }
}

void strReplace(char* string, char what[], char forWhat[], int sizeOfString){
    int strlenWhat = (int)strlen(what);
    int strlenForWhat = (int)strlen(forWhat);
    int strlenString = (int)strlen(string);
    int pos = 0;
    for(int i = 0; i < strlenString - strlenWhat;){
        for(int j = 0; j < strlenWhat; j++){
            if (string[j + i] != what[j]){
                i++;
                j = -1;
                continue;
            }
        }
        pos = i;
        break;
    }
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

int checkNumber(char element){
    if(element >= '0' && element <= '9'){
        return 1;
    }
    return 0;
}
int checkLetter(char element){
    if(element >= 'a' && element <= 'z' || element >= 'A' && element <= 'Z'){
        return 1;
    }
    return 0;
}

int checkSign(char element){
    if(element == '+' || element == '-' || element == '*' || element == '/' || element == '^' || element == ')' || element == '('){
        return 1;
    }
    return 0;
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
        if(checkNumber(expression[i])){
            timeSymbols[counterForTime++] = expression[i];
            while(checkNumber(expression[i+1])){
                timeSymbols[counterForTime++] = expression[i+1];
                i++;
            }
            for(int j = 0; j < counterForTime; j++){
                expressionWithSpaces[counterForSpaces++] = timeSymbols[j];
            }
            counterForSpaces++;
            counterForTime = 0;
            strclear(timeSymbols);
        } else if(checkLetter(expression[i])){
            timeSymbols[counterForTime++] = expression[i];
            while(checkLetter(expression[i+1]) || checkNumber(expression[i+1])){
                timeSymbols[counterForTime++] = expression[i+1];
                i++;
            }
            for(int k = 0; k < counterForTime; k++){
                expressionWithSpaces[counterForSpaces++] = timeSymbols[k];
            }
            counterForSpaces++;
            counterForTime = 0;
            strclear(timeSymbols);
        } else if(checkSign(expression[i])){
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

void delSpaces(char* expression){
    for(int i = 0; i < strlen(expression); i++){
        if (expression[i] == ' '){
            int j = i;
            while (j < strlen(expression)){
                expression[j] = expression[j+1];
                j++;
            }
            i--;
        }
    }
}

void strPrepare(char* expression){
    delSpaces(expression);
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



