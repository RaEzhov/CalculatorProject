#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct expressionNode{
    char status; //0 - not initialized 1 - sign 2 - number 3 - bracket
    char sign;
    double number;
    char bracket;
} EXPNODE;

#endif