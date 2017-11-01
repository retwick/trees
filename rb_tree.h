
/*creating a new node
arguments: key
return: pointer to the node created
*/
struct node* createNode(int );

/*insert by maintaining red-black property
arguments: pointer to root of tree, key
return: pointer to root.
*/
struct node* RBinsert(struct node* , int );

/*function to delete a node
arguments: pointer to the root, key
return: pointer to the root of the subtree where node is deleted
*/
struct node* delete(struct node* ,int);

/*query an element
arguments: pointer to root of tree, query element
return: pointer to node with key == query
*/
struct node * lookupNode(struct node* ptr, int key);

/*
function to find minimum value stored in the tree
arguments: pointer to the root
return: min value
*/
struct node * minVal(struct node* );

/*
function to get height of node
arguments: pointer to the node
return: heighht of node
*/
int height(struct node* );

void printLevelOrder(struct node* );

struct node* leftRotate(struct node *, int );

struct node* rightRotate(struct node *, int );

struct node* RBcolour(struct node **root, int key);