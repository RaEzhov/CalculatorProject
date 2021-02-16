#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

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

void in(NODE* root)
{
	if (root)
	{
		in(root->left);
		printf("%5d", root->val);
		in(root->right);
	}
}

NODE* DeleteFromTree(NODE* root, int val)
{
	return 0;
}
