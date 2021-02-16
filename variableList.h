#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#define variableLength 15

typedef struct variable {
    char name[variableLength];
    double value;
    struct variable* pointer;
}VARNODE;

void addToVariableList();
double retValue();

#endif //VARIABLELIST_H