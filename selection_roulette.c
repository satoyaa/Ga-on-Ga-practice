#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void selection_roulette(){
    int new_genes[POPULATION][MAX_NODES];
    double new_fitness[POPULATION];
    int best_gene[MAX_NODES];
    double best_fitness = fitness[0];
    // initialize best_gene with the first individual to avoid copying uninitialized data
    for (int k = 0; k < MAX_NODES; k++) {
        best_gene[k] = genes[0][k];
    }
    double sum_fitness = 0;
    for (int i = 0; i < POPULATION; i++)
    {
        sum_fitness+=fitness[i];
    }
    
    for(int i = 0; i < POPULATION; i++){
        double pivot = (double)rand()/RAND_MAX * sum_fitness;
        if(fitness[i]<best_fitness){
            for(int j=0; j<MAX_NODES; j++){
                best_gene[j] = genes[i][j];
            }  
            best_fitness = fitness[i];
        };
        double move_roulette = 0;
        int index = 0;
        for (int j = 0; j < POPULATION; j++)
        {
            move_roulette += fitness[j];
            if (pivot < move_roulette)
            {
                index = j;
                break;
            }
        }
        for(int j=0; j<MAX_NODES; j++){
            new_genes[i][j] = genes[index][j];
        }
        new_fitness[i] = fitness[index];
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