#ifndef TREE_H
#define TREE_H

typedef struct branch
{
    char status;  // 1 - sign 2 - number 4 - function
    char sign;
    double number;
    char function;
    struct branch* left, * right;
    struct branch* parent;
}BRANCH;

void addToTree(BRANCH** root, BRANCH node);
BRANCH* deleteTree(BRANCH * root);
//BRANCH* DeleteFromTree(BRANCH * root, int val);
//void PrintSym(BRANCH* root);
void PrintOnLeft(BRANCH* root, int level);

#endif //TREE_H