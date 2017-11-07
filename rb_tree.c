// C program to demonstrate insert operation in binary search tree
#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"  

/*
Structure definition of node
contains key, colour as integer values
left child, right child, parent pointers
*/

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
struct node* createNode(int key,struct node* nil){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = key;
	temp->left   = nil;
	temp->right  = nil;
	temp->parent = nil;
	temp->colour = 0;
	return temp;
}

/*
function which creates sentinel node
assigns black colour to it
*/
struct node* createNil(struct node **ptr){
	*ptr = createNode(-1,*ptr);
    (*ptr)->colour = 1;
}

/*
insert by maintaining BST property. 
only distinct values will be inserted.
arguments: pointer to root of tree, key
return: pointer to root.(necessary as we are using a recursive method)
*/
struct node* insert(struct node* root, int key,struct node* nil){
	if(root == nil){
		struct node *temp = createNode(key,nil);
		temp->parent = nil;
		return temp;
	}
	else if(key < root->key){
		root->left = insert(root->left, key, nil);
		root->left->parent = root;
	}
	else if(key > root->key){
		root->right = insert(root->right, key, nil);
		root->right->parent = root;
	}
	return root;
}

/*
Function to insert maintaning Red Black Tree properties
arguments: pointer to root, key value, pointer to nil
return: pointer to 
*/

struct node* RBinsert(struct node* root, int key, struct node* nil){
	root = insert(root, key, nil);
	struct node *z =lookupNode(root, key,nil);
	struct node *y = nil;
	while(z->colour != 1 && z != root && z->parent->colour == 0){
		//Parent of z is left child of Grand-parent of z
		if(z->parent == z->parent->parent->left){
			//y is the uncle of z
			y = z->parent->parent->right;
			if((y != nil) && (y->colour == 0)){
				//CASE 1
				//recolouring
				z->parent->colour = 1;
				y->colour = 1;
				z->parent->parent->colour = 0;
				z = z->parent->parent;
			}
			else {
				if(z == z->parent->right){
					//CASE 2-- left rotate at parent of x -- reduces to case 3
					z = z->parent;
					root = leftRotate(root,z->key,nil);
				}
				//CASE 3 -- right rotate at grandfather of z and do recolouring
				z->parent->colour = 1;
				z->parent->parent->colour = 0;
				root = rightRotate(root, z->parent->parent->key,nil);
				z = z->parent;
			}
		}

		else{
			y = z->parent->parent->left;
			if(y!= nil && y->colour == 0){
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
					root = rightRotate(root,z->key,nil);
				}
				//CASE 3
				z->parent->colour = 1;
				z->parent->parent->colour = 0;
				root = leftRotate(root, z->parent->parent->key,nil);
				z=z->parent;
			}
		}
	}
	root->colour = 1;
	return root;
}


/*
transplant function.
inputs: pointer to pointer of root, double pointer to u, double pointer to v, pointer to nil
return: void
node u will be replaced by node v, parent of u will become parent of v
*/
void RBtransplant(struct node** root,struct node** u, struct node** v, struct node* nil){
	if((*u)->parent == nil){
		*root = *v;
	}
	else if(*u == (*u)->parent->left){
		(*u)->parent->left = *v;
	}
	else {
		(*u)->parent->right = *v;
	}
	(*v)->parent = (*u)->parent;

}

/*
Function to delete maintaining red black properties
inputs: double pointer to root, key, pointer to nil
return: void
*/

void RBdelete(struct node **root,int key, struct node *nil){
	delete(root, lookupNode(*root, key,nil) ,nil);
}

/*function to delete a node
assuming the node to be deleted is the root of the subtree we delete the node.
arguments: pointer to the root, key
return: pointer to the root of the subtree where node is deleted
*/

struct node* delete(struct node** root,struct node* z, struct node* nil){
	//z is to be deleted
	if(z == nil){
		return *root;
	}

	if(*root == z){
		*root = nil;
	}
	struct node * temp;
	int originalColour = z->colour;
	//has only right sub tree
	if(z->left == nil){
		//transplanting z with z.right
		temp = z->right;
		RBtransplant(root,&z, &(z->right), nil);		
		}

		//has only left sub tree
	else if(z->right == nil){
		//transplanting z with z.left
		temp = z->left;
		RBtransplant(root, &z, &(z->left), nil);
		}

		/*
		has both left and right sub tree
		find min value of right sub tree = x
		put x at the the root
		delete x . 
		x will not have two subtrees, so this is reduced to previous case
		*/
	else{
		struct node* y = minVal(z->right,nil);	
		if(y == nil){
			printf("y is nill\n");
		}
		originalColour = y->colour;
		temp =y->right;
		if(y->parent == z)
				temp->parent = y;
		else{
			//transplant y with y.right
			RBtransplant(root, &y, &(y->right), nil);			

			y->right = z->right;
			y->right->parent = y;
		}
		RBtransplant(root, &z, &y, nil);
		y->left = z->left;
		y->left->parent = y;
		y->colour = z->colour;
	}
	if(originalColour == 1){
		RBheightfix(root,temp,nil); //temp is double black or red-black
	}	
}

/*
Function to maintain red black property after deletion
inputs: double pointer to root, pointer to node with double black, pointer to nil
return: pointer to root
*/
struct node* RBheightfix(struct node** root, struct node *x, struct node* nil){
	if(x == nil){		
		return nil;
	}
	struct node* s;
	while( x != *root && x->colour == 1){
		//case 1: x is left child of p(x)
		if(x == x->parent->left){
			s = x->parent->right;			
			//case 1.1 s is black
			if(s->colour == 1){
				//case 1.1.1 s.left is black, s.right is red
				if(s->left->colour == 1 && s->right->colour ==0){
					/*
					s.right.col to black
					swap colour of s and p(x)
					left rotate at p(x)
					make x single black
					*/								
					s->colour = x->parent->colour;
					x->parent->colour = 1;
					s->right->colour = 1;
					*root = leftRotate(*root, x->parent->key,nil);
					x = *root;				
				}
				//case 1.1.2 s.left is red,   s.right is red
				if(s->left->colour == 0 && s->right->colour ==0){
					/*
					s.right.col to black
					swap colour of s and p(x)
					left rotate at p(x)
					make x single black
					*/
					s->colour = x->parent->colour;
					x->parent->colour = 1;
					s->right->colour = 1;
					*root = leftRotate(*root, x->parent->key,nil);
					x = *root;
				}
				//case 1.1.3 s.left is red,   s.right is black
				if(s->left->colour == 0 && s->right->colour ==1){
					/*
					swap s.colour and s.left.colour
					right rotate at s
					reduces to case 1.1.1
					*/				
					s->colour = 0;
					s->left->colour = 1;
					*root = rightRotate(*root, s->key, nil);
					s = x->parent->right;	
				}
				//case 1.1.4 s.left is black, s.right is black
				if(s->left->colour == 1 && s->right->colour == 1){
					/*
					push blackness of x to p(x)
					p(x) will become double black if initially black 
					--this reduces to previous case with new x as p(x) 			
					make s red				
					*/
					
					x = x->parent;				
					s->colour = 0;	
				}
			}
			//case 1.2 s is red
			else{
				/*
				swap p(x).col and s.col
				left rotate at p(x)
				reduces to case 1.1
				*/
				x->parent->colour = 0;
				s->colour = 1;
				*root = leftRotate(*root,x->parent->key, nil);
				s = x->parent->right;			
			}
		}
	
		//case 2: x is right child of p(x)
		if(x == x->parent->right){		
			s = x->parent->left;
			
			//case 2.1 s is black
			if(s->colour == 1){
				//case 2.1.1 s.right is black, s.left is red
				if(s->right->colour == 1 && s->left->colour ==0){
					/*
					s.left.col to black
					swap colour of s and p(x)
					right rotate at p(x)
					make x single black
					*/								
					s->colour = x->parent->colour;
					x->parent->colour = 1;
					s->left->colour = 1;
					*root = rightRotate(*root, x->parent->key,nil);
					x = *root;				
				}
				//case 2.1.2 s.right is red,   s.left is red
				if(s->right->colour == 0 && s->left->colour ==0){
					/*
					s.left.col to black
					swap colour of s and p(x)
					right rotate at p(x)
					make x single black
					*/
					s->colour = x->parent->colour;
					x->parent->colour = 1;
					s->left->colour = 1;
					*root = rightRotate(*root, x->parent->key,nil);
					x = *root;
	
				}
				//case 2.1.3 s.right is red,   s.left is black
				if(s->right->colour == 0 && s->left->colour ==1){
					/*
					swap s.colour and s.right.colour
					left rotate at s
					reduces to case 1.1.1
					*/
					s->colour = 0;
					s->right->colour = 1;
					*root = leftRotate(*root, s->key, nil);
					s = x->parent->left;
	
				}
				//case 2.1.4 s.right is black, s.left is black
				if(s->right->colour == 1 && s->left->colour == 1){
					/*
					push blackness of x to p(x)
					p(x) will become double black if initially black 
					--this reduces to previous case with new x as p(x) 			
					make s red				
					*/
					
					x = x->parent;				
					s->colour = 0;
	
				}
			}
			//case 2.2 s is red
			else{
				/*
				swap p(x).col and s.col
				right rotate at p(x)
				reduces to case 1.1
				*/
				x->parent->colour = 0;
				s->colour = 1;
				*root = rightRotate(*root,x->parent->key, nil);
				s = x->parent->left;
			}
	
		} //end of case 2
	} //end of while	
	x->colour = 1;
}



/*
function to query an element
arguments: pointer to root of tree, query element
return: pointer to node with key == query
*/
struct node * lookupNode(struct node* ptr, int key, struct node* nil){
	if(ptr == nil){
		return nil;
	}
	else if(key < ptr->key){
		lookupNode(ptr->left,key,nil);
	}
	else if(key > ptr->key){
		lookupNode(ptr->right,key,nil);
	}
	else if(key == ptr->key){
		return ptr;
	}
	else
		return nil;
}

/*
function to find minimum value stored in the tree
arguments: pointer to the root
return: min value
*/
struct node* minVal(struct node* root, struct node* nil){
	if(root->left != nil){
		return(minVal(root->left, nil));	
	}	
	return root;
}

/*
function to get height of node
arguments: pointer to the node
return: heighht of node
*/
int height(struct node* root, struct node* nil){
	if(root == nil)
		return 1;

	int h_LST = height(root->left,nil);
	int h_RST = height(root->right,nil);
	int maxH;
	if(h_LST < h_RST){
		maxH = h_RST + 1;
	}
	else{
		maxH = h_RST + 1;
	}
	return (maxH);
}

/*
function to left rotate at key
arugments: pointer to root, key, pointer to nil
return: pointer to root
*/

struct node* leftRotate(struct node *root, int key, struct node* nil){
	//find parent of ptr, make parent of ptr as parent of ptr->right
	struct node* ptr = lookupNode(root, key,nil);
	struct node* ptr_right = ptr->right;


	ptr->right = ptr->right->left;

	if(ptr_right->left!=nil)
		ptr_right->left->parent = ptr;
	
	ptr_right->parent = ptr->parent;
	
	if(ptr->parent == nil){
		root = ptr_right;
	}
	else if (ptr == ptr->parent->left)
		ptr->parent->left = ptr_right;
	else
		ptr->parent->right = ptr_right;

	
	ptr_right->left = ptr;
	ptr->parent = ptr_right;
	
	root->parent = nil;
	return root;
}

/*
function to right rotate
arugments: pointer to root, key, pointer to nil
return: pointer to root
*/
struct node* rightRotate(struct node *root, int key, struct node* nil){
	//find parent of ptr, make parent of ptr as parent of ptr->left
	struct node* ptr = lookupNode(root, key,nil);
	struct node* ptr_left = ptr->left;


	ptr->left = ptr->left->right;
	if(ptr_left->right!=nil)
		ptr_left->right->parent = ptr;
	
	ptr_left->parent = ptr->parent;
	
	if(ptr->parent == nil){
		root = ptr_left;
	}
	else if (ptr == ptr->parent->right)
		ptr->parent->right = ptr_left;
	else
		ptr->parent->left = ptr_left;

	
	ptr_left->right = ptr;
	ptr->parent = ptr_left;
	
	root->parent = nil;
	return root;
}

/*
Function to print tree in level order
arguments: pointer to root, pointer to nil
return: void
*/
void printLevelOrder(struct node* root,struct node* nil)
{
    int h = height(root,nil);
    int i;
    for (i=1; i<=h; i++)
        printGivenLevel(root, i,nil);
}

/*
function to print a given level
arguments: pointer to root, level, pointer to nil
return: void
*/
 
void printGivenLevel(struct node* root, int level, struct node* nil)
{
    if (root == nil)
        return;
    if (level == 1)
        printf("%d :: parent = %d \t:: col = %d \n", root->key, root->parent->key, root->colour);
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1, nil);
        printGivenLevel(root->right, level-1, nil);
    }
}
