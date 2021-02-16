#include "variableList.h"
#include <stdlib.h>
#include <string.h>

void addToVariableList(VARNODE* list, char* name, double value){
    VARNODE * node = (VARNODE*)malloc(sizeof(VARNODE));
    strcpy(node->name, name);
    node->value = value;
    while(list->pointer){
        list = list->pointer;
    }
    list->pointer = node;
}