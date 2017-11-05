#include <stdio.h>
#include <stdlib.h>
#include "pointertree.h"
#include <time.h>

int randomKey(struct node*);

int main(int argc, char const *argv[]){	
	struct node* root = NULL;
    int i ;
    int count = 0;

    float start_time, end_time, tot_time;    
    //commamds for gnuplot
    char * commandsForGnuplot[] = {
        "set title \"partial rebuild trees \"",
        "set xlabel \"n\"", 
        "set ylabel \"time in milliseconds\"",
        "plot 'data.txt' with lines",
        "set term png",
        "set output \"plotass3.png\" ",
        "replot",
        "set term x11"
    };
    FILE * gnuplotPipe = popen ("gnuplot -persistent ", "w");

    //file for storing time taken
    FILE * fptr = fopen("data.txt", "w");

    srand(time(NULL));
    for(int num = 1024; num < 32000; num = num*2){
        start_time = clock();
        i = 0;
        while( i < num ){
            int t = rand()%3;
            if(t == 0){
                root = insert(root, rand());        
                ++count;
            }
            else if (t ==1) {
                if(root != NULL){
                   root = deleteNode(root,rand());
                    --count;
                }
            }
            else{
                lookupNode(root, rand());
            }                
         ++i;
        }
        
        end_time = clock();
        tot_time = 1000 * (end_time - start_time)/CLOCKS_PER_SEC; 
        
        //printf("%d :: \n", num);
        
    
        fprintf(fptr, "%d %f\n",num, tot_time/num);
    }

    for (int n=0; n < 8 ; n++){
        //Send commands to gnuplot one by one.
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[n]); 
    }
	return 0;
}
