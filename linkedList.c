#include "linkedList.h"
#include <stdlib.h>

void addToList(EXPNODE** list, char status, char* value){
    EXPNODE * node = (EXPNODE*)malloc(sizeof(EXPNODE));
    switch (status) {
        case 1:
            node->status = 1;
            node->bracket = 0;
            node->number = 0;
            node->function = 0;
            node->sign = value[0];
            break;
        case 2:
            node->status = 2;
            node->bracket = 0;
            node->sign = 0;
            node->function = 0;
            node->number = strtod(value, NULL);
            break;
        case 3:
            node->status = 3;
            node->number = 0;
            node->sign = 0;
            node->function = 0;
            node->bracket = value[0];
            break;
        case 4:
            node->status = 4;
            node->function = value[0];
            node->sign = 0;
            node->number = 0;
            node->bracket = 0;
            break;
        default:
            exit(-1);
    }
    node->pointer = NULL;

    if(*list == 0){
        *list = node;
        return;
    }
    while((*list)->pointer){
        list = &(*list)->pointer;
    }
    (*list)->pointer = node;
}

void clearList(EXPNODE* list){
    EXPNODE * prev = list;
    list = list->pointer;
    while(list->pointer){
        free(prev);
        prev = list;
        list = list->pointer;
    }
    free(prev);
    free(list);
}

void pushToStack(EXPNODE** top, EXPNODE newNode){
    EXPNODE * node = (EXPNODE*)malloc(sizeof(EXPNODE));
    *node = newNode;
    node->pointer = *top;
    *top = node;
}

EXPNODE popFromStack(EXPNODE** top){
    if(*top) {
        EXPNODE ret = **top;
        free(*top);
        *top = ret.pointer;
        return ret;
    }
    exit(-4);
}