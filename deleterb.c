#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h" 

/*
         /// <summary>
        /// Deletes a specified value from the tree
        /// </summary>
        /// <param name="item"></param>
        struct node* Delete(struct node* root, int key)
        {
            //first find the node in the tree to delete and assign to item pointer/reference
            struct node *item = lookupNode(root, key);
            struct node *X = NULL;
            struct node *Y = NULL;
 
            if (item == NULL)
            {
                //Console->WriteLine("Nothing to delete!");
                return root;
            }
            if (item->left == NULL || item->right == NULL)
            {
                Y = item;
            }
            else
            {
                Y = minValue(root, item->right);
                //Y = TreeSuccessor(item);
            }
            if (Y->left != NULL)
            {
                X = Y->left;
            }
            else
            {
                X = Y->right;
            }
            if (X != NULL)
            {
                X->parent = Y;
            }
            if (Y->parent == NULL)
            {
                root = X;
            }
            else if (Y == Y->parent->left)
            {
                Y->parent->left = X;
            }
            else
            {
                Y->parent->left = X;
            }
            if (Y != item)
            {
                item->data = Y->data;
            }
            if (Y->colour == 1)
            {
                DeleteFixUp(&root, X);
            }
            return root;
 
        }
        /// <summary>
        /// Checks the tree for any violations after deletion and performs a fix
        /// </summary>
        /// <param name="X"></param>
        struct node* DeleteFixUp(struct node **root, struct node* X)
        {
 
            while (X!= NULL && X != root && X->colour == 1)
            {
                if (X == X->parent->left)
                {
                    struct node* W = X->parent->right;
                    if (W->colour == 0)
                    {
                        W->colour = 1; //case 1
                        X->parent->colour = 0; //case 1
                        leftRotate(root, X->parent->key); //case 1
                        W = X->parent->right; //case 1
                    }
                    if (W->left->colour == 1 && W->right->colour == 1)
                    {
                        W->colour = 0; //case 2
                        X = X->parent; //case 2
                    }
                    else if (W->right->colour == 1)
                    {
                        W->left->colour = 1; //case 3
                        W->colour = 0; //case 3
                        rightRotate(root, W->key); //case 3
                        W = X->parent->right; //case 3
                    }
                    W->colour = X->parent->colour; //case 4
                    X->parent->colour = 1; //case 4
                    W->right->colour = 1; //case 4
                    leftRotate(root, X->parent->key); //case 4
                    X = root; //case 4
                }
                else //mirror code from above with "right" & "left" exchanged
                {
                    struct node *W = X->parent->left;
                    if (W->colour == 0)
                    {
                        W->colour = 1;
                        X->parent->colour = 0;
                        rightRotate(root,X->parent);
                        W = X->parent->left;
                    }
                    if (W->right->colour == 1 && W->left->colour == 1)
                    {
                        W->colour = 1;
                        X = X->parent;
                    }
                    else if (W->left->colour == 1)
                    {
                        W->right->colour = 1;
                        W->colour = 0;
                        leftRotate(root, W->key);
                        W = X->parent->left;
                    }
                    W->colour = X->parent->colour;
                    X->parent->colour = 1;
                    W->left->colour = 1;
                    rightRotate(root, X->parent->key);
                    X = root;
                }
            }
            if(X != NULL)
            X->colour = 1;
        }

*/

struct node * RBdelete(struct node * root, int key){
    root = delete(root, key);
    root = RBdeletecolour(root);
}