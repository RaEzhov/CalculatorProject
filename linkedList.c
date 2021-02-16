#include "linkedList.h"
#include <stdlib.h>

void addToList(EXPNODE* list, char status, char* value){
    EXPNODE * node = (EXPNODE*)malloc(sizeof(EXPNODE));
    switch (status) {
        case 1:
            node->status = 1;
            node->sign = value[0];
            break;
        case 2:
            node->status = 2;
            node->number = strtod(value, NULL);

            break;
        case 3:
            node->status = 3;
            node->bracket = value[0];
        default:
            exit(-1);
    }
    while(list->pointer){
        list = list->pointer;
    }
    list->pointer = node;
}

void pushToStack(EXPNODE* top, char status, char* value){
    EXPNODE * node = (EXPNODE*)malloc(sizeof(EXPNODE));
    switch (status) {
        case 1:
            node->status = 1;
            node->sign = value[0];
            break;
        case 2:
            node->status = 2;
            node->number = strtod(value, NULL);

            break;
        case 3:
            node->status = 3;
            node->bracket = value[0];
        default:
            exit(-1);
    }
    if (top){
        node->pointer = top;
        top = node;
    } else {
        top = node;
    }
}