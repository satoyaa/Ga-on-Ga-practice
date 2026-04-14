#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void selection_tournament(){
    int new_genes[POPULATION][MAX_NODES];
    double new_fitness[POPULATION];
    int r1;
    int r2;
    double fitness1;
    double fitness2;
    int best_gene[MAX_NODES];
    double best_fitness = fitness[0];
    // initialize best_gene with the first individual to avoid copying uninitialized data
    for (int k = 0; k < MAX_NODES; k++) {
        best_gene[k] = genes[0][k];
    }
    for(int i = 0; i < POPULATION; i++){
        if(fitness[i]<best_fitness){
            for(int j=0; j<MAX_NODES; j++){
                best_gene[j] = genes[i][j];
            }  
            best_fitness = fitness[i];
        };
        r1 = rand() % POPULATION;
        r2 = rand() % POPULATION;
        fitness1 = fitness[r1];
        fitness2 = fitness[r2];
        if(fitness1 < fitness2){
            for(int j=0; j<MAX_NODES; j++){
                new_genes[i][j] = genes[r1][j];
            }           
            new_fitness[i] = fitness[r1];
        }else{
            for(int j=0; j<MAX_NODES; j++){
                new_genes[i][j] = genes[r2][j];
            }
            new_fitness[i] = fitness[r2];
        }
    }
    for(int j=0; j<MAX_NODES; j++){
        genes[0][j] = best_gene[j];
    }    
    fitness[0] = best_fitness;
    for(int i=1; i<POPULATION; i++){
        for(int j=0; j<MAX_NODES; j++){
            genes[i][j] = new_genes[i][j];
        }    
        fitness[i] = new_fitness[i];
    }
}