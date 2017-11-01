#include <stdio.h>
#include "rb_tree.h"
#include <time.h>
#include <stdlib.h>



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
    root = RBinsert(root,10);
    root = RBinsert(root,26);
    root = RBinsert(root,8);
    printLevelOrder(root);
    printf("\n");
 
    //root = RBcolour(root,1);
    //root = RBcolour(root,6);
    //RBcolour(&root,4);
    root = delete(root,10);
    printLevelOrder(root);
    printf("\n");
 
    return 0;
}