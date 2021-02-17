#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#define variableLength 15

typedef struct variable {
    char name[variableLength];
    double value;
    struct variable* pointer;
}VARNODE;

void addToVariableList(VARNODE** list, char* name, double value);
double retValue(VARNODE* list, char* name);
void clearVarList(VARNODE* list);

#endif //VARIABLELIST_H