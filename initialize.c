#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"



void shuffle(int i){
    for(int j = MAX_NODES-1; 0 <= j; j--){
        int r = rand() % MAX_NODES;  
        while (genes[i][r] != -1)
        {
            r += 2;
            if(MAX_NODES+1 == r){r = 1;}else if(MAX_NODES-1<r){r=0;}
        }
        // store node index (0-based) to match nodes[] indexing
        genes[i][r] = j;

    }
    
}

void initialize(){
    for(int i=0; i<POPULATION; i++){
        for(int j=0;j<MAX_NODES; j++){
            genes[i][j] = -1;
        }
    }

    for(int i=0; i < POPULATION; i++){
        shuffle(i);   
    }
}