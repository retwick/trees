#include <stdio.h>
#include "partial_tree.h"

//implement rotation


int main(int argc, char const *argv[])
{
	struct node* root = NULL;
	root = RBinsert(root,3);
	root = RBinsert(root,2);
	root = RBinsert(root,5);
	root = RBinsert(root,1);
	root = RBinsert(root,4);
	root = RBinsert(root,6);
	root = RBinsert(root,7);
	root = RBinsert(root,15);
	root = RBinsert(root,26);
	
	printLevelOrder(root);
	printf("\n");

	return 0;
}