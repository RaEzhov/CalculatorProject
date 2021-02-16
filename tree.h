#pragma once

typedef struct Node
{
	int val;
	struct Node* left, * right;
}NODE;

NODE * Add2Tree(NODE* root, int val);
NODE* DeleteTree(NODE* root);
void in(NODE* root);
NODE* DeleteFromTree(NODE* root, int val);