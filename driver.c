#include <stdio.h>
#include "rb_tree.h"
#include <time.h>
#include <stdlib.h>

struct node* RBheightfix(struct node* );

int main(int argc, char const *argv[])
{
    void dbprint(struct node*);
    struct node* root = NULL;
    root = RBinsert(root,3);
    root = RBinsert(root,2);
    root = RBinsert(root,5);
    root = RBinsert(root,1);
    root = RBinsert(root,4);
    root = RBinsert(root,6);
    root = RBinsert(root,7);
    root = RBinsert(root,15);
    root = RBinsert(root,10);
    root = RBinsert(root,26);
    root = RBinsert(root,8);
    printLevelOrder(root);
    printf("\n");
 
    //root = RBcolour(root,1);
    //root = RBcolour(root,6);
    //RBcolour(&root,4);
    delete(&root,4);
    printLevelOrder(root);
    printf(" \n");
    root = RBheightfix(root);
    printLevelOrder(root);
    
    
 
    return 0;
}