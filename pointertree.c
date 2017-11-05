// C program to demonstrate insert operation in binary search tree
#include <stdio.h>
#include <stdlib.h>
#include "pointertree.h"  
struct node
{
    int key;
    struct node *left, *right;
};

/*creating a new node
arguments: key
return: pointer to the node created
*/

struct node* createNode(int key){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

/*in order traverse
arguments: pointer to root of tree
return: null
*/
void traverse(struct node* root){
	if(root != NULL){
		traverse(root->left);
		printf("%d ",root->key); 
		traverse(root->right);
	}
}

/*insert by maintaining BST property. only distinct values will be inserted
arguments: pointer to root of tree, key
return: pointer to root.(necessary as we are using a recursive method)
*/
struct node* insert(struct node* root, int key){
	if(root == NULL){
		return createNode(key);
	}
	else if(key < root->key){
		root->left = insert(root->left, key);
	}
	else if(key > root->key){
		root->right = insert(root->right, key);
	}
	if(key == root->key)
		return NULL;
	root = rebuildTree(root);
	return root;
}

/*query an element
arguments: pointer to root of tree, query element
return: pointer to node with key == query
*/
struct node * lookupNode(struct node* ptr, int key){
	if(ptr == NULL){
		return NULL;
	}
	else if(key < ptr->key){
		lookupNode(ptr->left,key);
	}
	else if(key > ptr->key){
		lookupNode(ptr->right,key);
	}
	else if(key == ptr->key)
		return ptr;
	else
		return NULL;
}
/*
function to find minimum value stored in the tree
arguments: pointer to the root
return: min value
*/
struct node* minVal(struct node* root){
	if(root->left == NULL){
		return root;
	}
	minVal(root->left);
}
/*function to delete a node
	assuming the node to be deleted is the root of the subtree we delete the node.
arguments: pointer to the root, key
return: pointer to the root of the subtree where node is deleted
*/
struct node* deleteNode(struct node* root,int key){
	if(root == NULL){
		return root;
	}
	if(key == root->key){
		//node is a leaf
		if((root->left == NULL)&&(root->right == NULL)){
			free(root);
			return NULL;
		}
		//has only right sub tree
		else if(root->left == NULL){
			struct node* temp = root;
			free(root);
			return temp->right;
		}
		//has only left sub tree
		else if(root->right == NULL){
			struct node* temp = root;
			free(root);
			return temp->left;
		}
		/*
		has both left and right sub tree
		find min value of right sub tree = x
		put x at the the root
		delete x . 
		x will not have two subtrees, so this is reduced to previous case
		*/
		else{
			int x = (minVal(root->right))->key;
			root->key = x;
			root->right = deleteNode(root->right,x);
			return root;
		}
	}
	else if(key < root->key){
		root->left = deleteNode(root->left,key);
	}
	else if(key > root->key){
		root->right = deleteNode(root->right,key);
	}
	return root;
}
/*
function to get height of node
arguments: pointer to the node
return: heighht of node
*/
int height(struct node* root){
	if(root == NULL)
		return 0;
	//if( (root->left == NULL) && (root->right == NULL) ){
	//	return 1;
	//}

	int h_LST = height(root->left);
	int h_RST = height(root->right);
	int maxH;
	if(h_LST < h_RST){
		maxH = h_RST + 1;
	}
	else{
		maxH = h_RST + 1;
	}
	return maxH;
}

int randomKey(struct node* root){
	if(root == NULL){
		return 0;
	}
	if(root->left != NULL){
		if(rand()%2 == 0)
			return randomKey(root->left);
		else
			return root->key;
	}
	if(root->right != NULL){
		if(rand()%2 == 0)
			return randomKey(root->right);
		else
			return root->key;
	}
}

int size(struct node* root){
	if(root == NULL){ 
		return 1;
	}
	return(size(root->left) + size(root->right));
}


struct node* sortedToTree(int arr[], int start, int end)
{

    if (start > end)
      return NULL;
 
    int mid = start + (end - start)/2;
    struct node *root = createNode(arr[mid]);
 
    root->left =  sortedToTree(arr, start, mid-1);
 
    root->right = sortedToTree(arr, mid+1, end);
 
    return root;
}

struct node* rebuildTree(struct node *root){
	if(root == NULL)
		return NULL;
	if((size(root->left) <= size(root)/2) || (size(root->right) <= size(root)/2))
		return root;
	int sizeRoot = size(root);
	int arr[sizeRoot-1];
	int i;
	for (i = 0; i < sizeRoot - 1; ++i){
		arr[i] = minVal(root)->key;
		//printf("%d \n",lookupNode(root,arr[i])->key);
		root = deleteNode(root, arr[i]);
	}
	/*printf("rebuildTree sorted array:\n");
	for (int i = 0; i < sizeRoot-1; ++i){
			printf("%d ", arr[i]);
		}	
	*/
	root = sortedToTree(arr,0, i - 1);
	return root;
}

void printLevelOrder(struct node* root)
{
    int h = height(root);
    int i;
    for (i=1; i<=h; i++)
        printGivenLevel(root, i);
}
 
void printGivenLevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d @ %d\t", root->key, height(root));
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}
