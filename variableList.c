#include "variableList.h"
#include <stdlib.h>
#include <string.h>

void addToVariableList(VARNODE** list, char* name, double value){
    VARNODE * node = (VARNODE*)malloc(sizeof(VARNODE));
    strcpy(node->name, name);
    node->value = value;
    node->pointer = 0;
    if (*list == 0){
        *list = node;
        return;
    }
    while((*list)->pointer){
        list = &((*list)->pointer);
    }
    (*list)->pointer = node;
}

double retValue(VARNODE* list, char* name){
    while((strcmp(list->name, name) != 0 && list != 0)){
        list = list->pointer;
    }
    if (list == 0){
        exit(-2);
    }
    return list->value;
}

void clearVarList(VARNODE* list){
    VARNODE * prev = list;
    list = list->pointer;
    while(list->pointer){
        free(prev);
        prev = list;
        list = list->pointer;
    }
    free(prev);
    free(list);
}