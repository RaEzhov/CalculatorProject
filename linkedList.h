#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct expressionNode{
    char status; //0 - space 1 - sign 2 - number 3 - bracket 4 - function
    char sign;
    double number;
    char bracket;
    char function;
    struct expressionNode* pointer;
} EXPNODE;

void addToList(EXPNODE** list, char status, char* value);
void clearList(EXPNODE* list);

void pushToStack(EXPNODE** top, EXPNODE node);
EXPNODE popFromStack(EXPNODE** top);

#endif //LINKEDLIST_H