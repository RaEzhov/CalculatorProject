#include "tree.h"
#include <stdlib.h>

BRANCH* allocateMemory(){
    return (BRANCH*)malloc(sizeof (BRANCH));
}

void addToTree(BRANCH** root, BRANCH node)
{
    if (!(*root))
    {
        *root = allocateMemory();
        **root = node;
        (*root)->parent = (*root)->left = (*root)->right = NULL;
    }
    else {
        if ((*root)->status == 2){
            (*root) = (*root)->parent;
        }
        if (!(*root)->right) {
            (*root)->right = allocateMemory();
            *((*root)->right) = node;
            (*root)->right->parent = (*root);
            (*root) = (*root)->right;
        } else {
            while ((*root)->left && (*root)->status != 4) {
                (*root) = (*root)->parent;
            }
            (*root)->left = allocateMemory();
            *((*root)->left) = node;
            (*root)->left->parent = (*root);
            (*root) = (*root)->left;
        }
    }
}

BRANCH* deleteTree(BRANCH* root)
{
    if (root)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
    return 0;
}