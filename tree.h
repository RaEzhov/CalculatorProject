#pragma once

typedef struct Node
{
    int val;
    struct Node* left, * right;
}NODE;

NODE * Add2Tree(NODE* root, int val);
NODE* DeleteTree(NODE* root);
NODE* DeleteFromTree(NODE* root, int val);
void PrintSym(NODE* root);
void PrintOnLeft(NODE* root, int level);