#include <stdio.h>
#include "rb_tree.h"
#include <time.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    int sel;
    int i ;
    float start_time, end_time, tot_time;    
    //commamds for gnuplot
    char * commandsForGnuplot[] = {
        "set title \"red black trees \"",
        "set xlabel \"number of operations\"", 
        "set ylabel \"average time in milliseconds\"",
        "plot 'data.txt' with lines ",
        "set term png",
        "set output \"plot.png\" ",
        "replot",
        "set term x11"
    };

    printf("Input :\n1 for insert \n2 for delete\n3 for look up\n");
    scanf("%d", &sel);
 
    FILE * gnuplotPipe = popen ("gnuplot -persistent ", "w");

    //file for storing time taken
    FILE * fptr = fopen("data.txt", "w");

    srand(time(NULL)); 

    for(int num = 1024; num < 31000; num = num+50){
        struct node* nil = NULL;
        createNil(&nil);
        struct node* root = nil;
 
        start_time = clock();
        i = 0;        
        while( i < 10 ){            
        	root = RBinsert(root, i, nil);  
		if(sel == 2) { RBdelete(&root,rand(),nil); }
		if(sel ==3) { lookupNode(root, rand(), nil); }
		printLevelOrder(root,nil);
		printf("\n");
		++i;
        } //end of while
       
        end_time = clock();
        tot_time = 1000 * (end_time - start_time)/CLOCKS_PER_SEC;         
       	fprintf(fptr, "%d %f\n",num, tot_time/num);
	break;
    }



    for (int n=0; n < 8 ; n++){
        //Send commands to gnuplot one by one.
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[n]); 
    }
 
   return 0;  
}
