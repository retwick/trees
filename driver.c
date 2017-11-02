#include <stdio.h>
#include "rb_tree.h"
#include <time.h>
#include <stdlib.h>

struct node* RBheightfix(struct node* );

int main(int argc, char const *argv[])
{
    void dbprint(struct node*);
    struct node* nil = NULL;
    createNil(&nil);
    struct node* root = nil;
    root = RBinsert(root,3,nil);
    root = RBinsert(root,2,nil);
    root = RBinsert(root,5,nil);
    root = RBinsert(root,1,nil);
    root = RBinsert(root,4,nil);
    root = RBinsert(root,6,nil);
    root = RBinsert(root,7,nil);
    root = RBinsert(root,15,nil);
    root = RBinsert(root,10,nil);
    root = RBinsert(root,26,nil);
    root = RBinsert(root,8,nil);
    /**/
    printLevelOrder(root,nil);
    printf("\n");
 
    //root = RBcolour(root,1);
    //root = RBcolour(root,6);
    //RBcolour(&root,4);
    //delete(&root,4);
    //printLevelOrder(root,nil);
    printf(" \n");
    //root = RBheightfix(root);
    //printLevelOrder(root);
    
    
 
    return 0;
}