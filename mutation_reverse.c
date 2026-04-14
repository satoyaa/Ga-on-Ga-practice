#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void mutation_reverse(){
    int start = rand()%MAX_NODES;
    int end = rand()%MAX_NODES;
    if(end<start){
        int temp = end;
        end = start;
        start = temp;
    }
    int temp;
    for(int i = 0;i<POPULATION;i++){
        double r = (double)rand()/RAND_MAX;
        if (mutation_rate < r){continue;}
        
        for (int j = start; j < end/2; j++)
        {
            temp = genes[i][j];
            genes[i][j] = genes[i][end-j];
            genes[i][end-j] = temp;
            
        }
        
    }
}