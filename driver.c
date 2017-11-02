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
 
    printLevelOrder(root,nil);
    printf("\n");
 
    //root = RBcolour(root,1);
    //root = RBcolour(root,6);
    //RBcolour(&root,4);
    RBdelete(&root,15,nil);
    printLevelOrder(root,nil);
    printf(" \n");
    //root = RBheightfix(root);
    //printLevelOrder(root);
  

/*
    int i ;
    float start_time, end_time, tot_time;    
    //commamds for gnuplot
    char * commandsForGnuplot[] = {
        "set title \"red black trees \"",
        "set xlabel \"number of operations\"", 
        "set ylabel \"average time in milliseconds\"",
        "plot 'data.txt' with lines",
        "set term png",
        "set output \"plot.png\" ",
        "replot",
        "set term x11"
    };
    FILE * gnuplotPipe = popen ("gnuplot -persistent ", "w");

    //file for storing time taken
    FILE * fptr = fopen("data.txt", "w");

    srand(time(NULL)); 

    for(int num = 1024; num < 31000; num = num+1000){
        start_time = clock();
        i = 0;
        while( i < num ){
           root = RBinsert(root, rand(), nil);
           ++i;
        } //end of while
       
        end_time = clock();
        tot_time = 1000 * (end_time - start_time)/CLOCKS_PER_SEC; 
        
        //printf("%d :: \n", num);           
       fprintf(fptr, "%d %f\n",num, tot_time/num);
    }

    for (int n=0; n < 8 ; n++){
        //Send commands to gnuplot one by one.
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[n]); 
    }
    */
   return 0;  
}