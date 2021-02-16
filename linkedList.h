#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#define numberLength 20

typedef struct expressionNode{
    char status; //0 - not initialized 1 - sign 2 - number 3 - bracket
    char sign;
    double number;
    char bracket;
    struct expressionNode* pointer;
} EXPNODE;




void pushToStack(EXPNODE* top, char status, char* value));

#endif