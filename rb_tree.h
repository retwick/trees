
/*creating a new node
arguments: key
return: pointer to the node created
*/
struct node* createNode(int, struct node* );

/*insert by maintaining red-black property
arguments: pointer to root of tree, key
return: pointer to root.
*/
struct node* RBinsert(struct node* , int , struct node*);

/*function to delete a node
arguments: pointer to the root, key
return: pointer to the root of the subtree where node is deleted
*/
struct node* delete(struct node**, struct node* ,struct node*);

/*query an element
arguments: pointer to root of tree, query element
return: pointer to node with key == query
*/
struct node * lookupNode(struct node* , int , struct node*);

/*
function to find minimum value stored in the tree
arguments: pointer to the root
return: min value
*/
struct node * minVal(struct node* , struct node*);

/*
function to get height of node
arguments: pointer to the node
return: heighht of node
*/
int height(struct node*, struct node* );

/*
function to left rotate at key
arugments: pointer to root, key, pointer to nil
return: pointer to root
*/

struct node* leftRotate(struct node *, int, struct node * );

/*
function to right rotate at key
arugments: pointer to root, key, pointer to nil
return: pointer to root
*/
struct node* rightRotate(struct node *, int, struct node* );

/*
Function to print tree in level order
arguments: pointer to root, pointer to nil
return: void
*/
void printLevelOrder(struct node* ,struct node* );

/*
function to print a given level
arguments: pointer to root, level, pointer to nil
return: void
*/
void printGivenLevel(struct node* , int , struct node* );

/*
function which creates sentinel node
assigns black colour to it
*/
struct node* createNil(struct node **);

/*
Function to delete maintaining red black properties
inputs: double pointer to root, key, pointer to nil
return: void
*/
void RBdelete(struct node **,int, struct node*);

/*
Function to maintain red black property after deletion
inputs: double pointer to root, pointer to node with double black, pointer to nil
return: pointer to root
*/
struct node* RBheightfix(struct node** , struct node*, struct node* );
