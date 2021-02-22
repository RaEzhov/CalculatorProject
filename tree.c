#include "tree.h"
#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

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
/*
void PrintSym(BRANCH* root)
{
    if (root)
    {
        PrintSym(root->left);
        printf("%5d", root->val);
        PrintSym(root->right);
    }
}

void Remove(BRANCH** root, int* val)
{
    while ((*root)->left)
    {
        root = &((*root)->left);
    }
    *val = (*root)->val;
}

BRANCH* DelNode(BRANCH* root)
{
    if (!root->left && !root->right)
    {
        free(root);
        return 0;
    }
    if (root->left && !root->right || !root->left && root->right)
    {
        BRANCH* p;
        if (root->left)
        {
            p = root->left;
        }
        else
        {
            p = root->right;
        }
        free(root);
        return p;
    }
    if (root->left && root->right)
    {
        int a=0;
        Remove(&root->right, &a);
        root->val = a;
        root->right = DeleteFromTree(root->right, a);
        return root;
    }
}

BRANCH* DeleteFromTree(BRANCH* root, int val)
{
    if (!root)
    {
        return 0;
    }
    if (root->val == val)
    {
        return DelNode(root);
    }
    if (root->val > val)
    {
        root->left = DeleteFromTree(root->left, val);
    }
    else
    {
        root->right = DeleteFromTree(root->right, val);
    }
    return root;
}

 */
void PrintOnLeft(BRANCH* root, int level)
{
    if (root)
    {
        PrintOnLeft(root->right, level + 1);
        for (int i = 0; i < level; ++i)
        {
            printf("   ");
        }
        printf("%d (%d)\n", root->status, level);
        PrintOnLeft(root->left, level + 1);
    }

}
