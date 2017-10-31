#include <stdio.h>
#include "partial_tree.h"

//implement rotation


int main(int argc, char const *argv[])
{
	struct node* root = NULL;
	root = insert(root,3);
	root = insert(root,2);
	root = insert(root,5);
	root = insert(root,1);
	root = insert(root,4);
	root = insert(root,6);
	root = insert(root,7);
	//root = insert(root,15);
	//root = insert(root,26);
	//root = delete(root,20);
	printLevelOrder(root);
	printf("\n");
	root = leftRotate(root, 3);
	printLevelOrder(root);
	printf("\n");
	root = rightRotate(root,5);
	printLevelOrder(root);
	printf("\n");
	return 0;
}