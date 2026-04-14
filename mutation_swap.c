#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void mutation_swap(){
    int point1 = rand()%MAX_NODES;
    int point2 = rand()%MAX_NODES;
    for(int i = 0;i<POPULATION;i++){
        double r = (double)rand()/RAND_MAX;
        if (mutation_rate < r){continue;}
        int temp = genes[i][point1];
        genes[i][point1] = genes[i][point2];
        genes[i][point2] = temp;        
    }
}