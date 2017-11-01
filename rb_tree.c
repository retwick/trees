// C program to demonstrate insert operation in binary search tree
#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"  
struct node
{
    int key, colour;
    struct node *left, *right, *parent;
};



/*creating a new node
arguments: key
return: pointer to the node created
colour field 0 means red 1 means black
*/
struct node* createNode(int key){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	temp->colour = 0;
	return temp;
}


/*insert by maintaining BST property. only distinct values will be inserted
arguments: pointer to root of tree, key
return: pointer to root.(necessary as we are using a recursive method)
*/
struct node* insert(struct node* root, int key){
	if(root == NULL){
		struct node *temp = createNode(key);
		temp->parent = temp;
		return temp;
	}
	else if(key < root->key){
		root->left = insert(root->left, key);
		root->left->parent = root;
	}
	else if(key > root->key){
		root->right = insert(root->right, key);
		root->right->parent = root;
	}
	return root;
}



struct node* RBinsert(struct node* root, int key){
	root = insert(root, key);
	struct node *z =lookupNode(root, key);
	struct node *y = NULL;
	while(z->parent->colour == 0 && z->parent != z ){
		if(z->parent== z->parent->parent->left){
			y = z->parent->parent->right;
			if((y != NULL) && (y->colour == 0)){
				//CASE 1
				z->parent->colour = 1;
				y->colour = 1;
				z->parent->parent->colour = 0;
				z = z->parent->parent;
			}
			else {
				if(z == z->parent->right){
					//CASE 2
					z = z->parent;
					root = leftRotate(root,z->key);
				}
				//CASE 3
				z->parent->colour = 1;
				z->parent->parent->colour = 0;
				root = rightRotate(root, z->parent->parent->key);
				z = z->parent;
			}
		}

		else{
			y = z->parent->parent->left;
			if(y!= NULL && y->colour == 0){
				//CASE 1
				z->parent->colour = 1;
				y->colour = 1;
				z->parent->parent->colour = 0;
				z = z->parent->parent;
			}
			else{ 
					if(z == z->parent->left){
					//CASE 2
					z = z->parent;
					root = rightRotate(root,z->key);
				}
				//CASE 3
				z->parent->colour = 1;
				z->parent->parent->colour = 0;
				root = leftRotate(root, z->parent->parent->key);
				z=z->parent;
			}
		}
	}
	root->colour = 1;

}

/*************************************************************************
MUST IMPLEMENT SENTINEL NODE
*************************************************************************/

struct node* RBcolour(struct node *root, int key){
	//v is the node to be deleted
	//u is the node to replace v
	
	struct node* v = lookupNode(root, key);
	struct node* u ;
	//deleting a node with atleast one child
	if(v->left != NULL && v->right == NULL){
		u = v->left;
		u->colour = 1;
	}
	else if(v->left == NULL && v->right != NULL){
		u = v->right;
		u->colour = 1;
	}
	//delting leaf node
	else if(v->left == NULL && v->right == NULL){
		u = v->parent;
/*		u->parent = v->parent->parent;
		if(u->parent->key < v->parent->parent->key)
			v->parent->parent->left = u;
		else
			v->parent->parent->right = u;
*/
		u->colour += v->colour;
	}
	
	return root;

}


/*function to delete a node
	assuming the node to be deleted is the root of the subtree we delete the node.
arguments: pointer to the root, key
return: pointer to the root of the subtree where node is deleted
*/
struct node* delete(struct node* root,int key){
	if(root == NULL){
		return root;
	}
	if(key == root->key){
		//node is a red leaf
		//done
		if((root->left == NULL)&&(root->right == NULL)){	
			root = RBcolour(root,root->key);	
			free(root);
			return NULL;
		}
		//has only right sub tree
		else if(root->left == NULL){
			root = RBcolour(root,root->key);
			struct node* temp = root;
			free(root);
			return temp->right;
		}
		//has only left sub tree
		else if(root->right == NULL){
			root = RBcolour(root,root->key);
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
			root->right = delete(root->right,x);
			return root;
		}
	}
	else if(key < root->key){
		root->left = delete(root->left,key);
	}
	else if(key > root->key){
		root->right = delete(root->right,key);
	}
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

/*
function to get height of node
arguments: pointer to the node
return: heighht of node
*/
int height(struct node* root){
	if(root == NULL)
		return 0;

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


/* frunction prototypes */
struct node** createQueue(int *, int *);
void enQueue(struct node **, int *, struct node *);
struct node *deQueue(struct node **, int *);
 
/* Given a binary tree, print its nodes in level order
   using array for implementing queue */
void printLevelOrder(struct node* root)
{
    int rear, front;
    struct node **queue = createQueue(&front, &rear);
    struct node *temp_node = root;
 
    while (temp_node)
    {
        printf("%d : %d :: %d\n", temp_node->key, temp_node->parent->key, temp_node->colour);
 
        /*Enqueue left child */
        if (temp_node->left)
            enQueue(queue, &rear, temp_node->left);
 
        /*Enqueue right child */
        if (temp_node->right)
            enQueue(queue, &rear, temp_node->right);
 
        /*Dequeue node and make it temp_node*/
        temp_node = deQueue(queue, &front);
    }
}
 
/*UTILITY FUNCTIONS*/
struct node** createQueue(int *front, int *rear)
{
    struct node **queue =
        (struct node **)malloc(sizeof(struct node*)*32768);
 
    *front = *rear = 0;
    return queue;
}
 
void enQueue(struct node **queue, int *rear, struct node *new_node)
{
    queue[*rear] = new_node;
    (*rear)++;
}
 
struct node *deQueue(struct node **queue, int *front)
{
    (*front)++;
    return queue[*front - 1];
}

/*
left rotate at P 
        ------->
	P				Q
   / \			   / \
  A	 Q			  P   C
    / \			 / \
   B   C		A   B
*/

struct node* leftRotate(struct node *root, int key){
	//find parent of ptr, make parent of ptr as parent of ptr->right
	struct node* ptr = lookupNode(root, key);
	struct node* ptr_right = ptr->right;


	ptr->right = ptr->right->left;
	//!=NIL
	if(ptr_right->left!=NULL)
		ptr_right->left->parent = ptr;
	
	ptr_right->parent = ptr->parent;
	
	// == NIL
	if(ptr->parent == ptr){
		root = ptr_right;
	}
	else if (ptr == ptr->parent->left)
		ptr->parent->left = ptr_right;
	else
		ptr->parent->right = ptr_right;

	
	ptr_right->left = ptr;
	ptr->parent = ptr_right;
	
	root->parent = root;
	return root;
}

struct node* rightRotate(struct node *root, int key){
	//find parent of ptr, make parent of ptr as parent of ptr->left
	struct node* ptr = lookupNode(root, key);
	struct node* ptr_left = ptr->left;


	ptr->left = ptr->left->right;
	if(ptr_left->right!=NULL)
		ptr_left->right->parent = ptr;
	
	ptr_left->parent = ptr->parent;
	
	if(ptr->parent == ptr){
		root = ptr_left;
	}
	else if (ptr == ptr->parent->right)
		ptr->parent->right = ptr_left;
	else
		ptr->parent->left = ptr_left;

	
	ptr_left->right = ptr;
	ptr->parent = ptr_left;
	
	root->parent = root;
	return root;
}