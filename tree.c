#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

NODE* Add2Tree(NODE* root, int val)
{
    if (!root)
    {
        root = (NODE*)malloc(sizeof(NODE));
        root->val = val;
        root->left = root->right = 0;
    }
    else
    {
        if (root->val > val)
        {
            root->left = Add2Tree(root->left, val);
        }
        else
        {
            root->right = Add2Tree(root->right, val);
        }
    }
    return root;
}

NODE* DeleteTree(NODE* root)
{
    if (root)
    {
        DeleteTree(root->left);
        DeleteTree(root->right);
        free(root);
    }
    return 0;
}

void PrintSym(NODE* root)
{
    if (root)
    {
        PrintSym(root->left);
        printf("%5d", root->val);
        PrintSym(root->right);
    }
}

void Remove(NODE** root, int* val)
{
    while ((*root)->left)
    {
        root = &((*root)->left);
    }
    *val = (*root)->val;
}

NODE* DelNode(NODE* root)
{
    if (!root->left && !root->right)
    {
        free(root);
        return 0;
    }
    if (root->left && !root->right || !root->left && root->right)
    {
        NODE* p;
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

NODE* DeleteFromTree(NODE* root, int val)
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

void PrintOnLeft(NODE* root, int level)
{
    if (root)
    {
        PrintOnLeft(root->right, level + 1);
        for (int i = 0; i < level; ++i)
        {
            printf("   ");
        }
        printf("%d (%d)\n", root->val, level);
        PrintOnLeft(root->left, level + 1);
    }

}
