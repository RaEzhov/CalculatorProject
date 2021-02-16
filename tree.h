#pragma once

typedef struct Node
{
    int val;
    struct Node* left, * right;
}NODE;

NODE * Add2Tree(NODE* root, int val);
NODE* DeleteTree(NODE* root);
void PrintSym(NODE* root);
NODE* DeleteFromTree(NODE* root, int val);
void PrintOnLeft(NODE* root, int level);