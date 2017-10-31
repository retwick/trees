
/*creating a new node
arguments: key
return: pointer to the node created
*/
struct node* createNode(int key);

/*insert by maintaining BST property
arguments: pointer to root of tree, key
return: pointer to root.
*/
struct node* insert(struct node* root, int key);

/*function to delete a node
arguments: pointer to the root, key
return: pointer to the root of the subtree where node is deleted
*/
struct node* delete(struct node* root,int key);

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
struct node * minVal(struct node* root);

/*
function to get height of node
arguments: pointer to the node
return: heighht of node
*/
int height(struct node* root);

void printLevelOrder(struct node* root);

struct node* rebuildTree(struct node *root);

struct node* leftRotate(struct node *, int );

struct node* rightRotate(struct node *, int );