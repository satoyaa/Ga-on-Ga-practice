#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void hyper_selection_tournament(){
    HyperGenes new_hyperGenes[POPULATION_OF_HYPER_GA][MAX_HYPER_GENES];
    double new_hyper_fitness[POPULATION_OF_HYPER_GA];
    HyperGenes best_hyper[MAX_HYPER_GENES];

    /* initialize best as the first individual */
    double best_f = hyper_fitness[0];
    memcpy(best_hyper, hyperGenes[0], sizeof(best_hyper));

    for(int i = 0; i < POPULATION_OF_HYPER_GA; i++){
        /* update best */
        if(hyper_fitness[i] < best_f){
            best_f = hyper_fitness[i];
            memcpy(best_hyper, hyperGenes[i], sizeof(best_hyper));
        }

        int r1 = rand() % POPULATION_OF_HYPER_GA;
        int r2 = rand() % POPULATION_OF_HYPER_GA;

        int winner = (hyper_fitness[r1] < hyper_fitness[r2]) ? r1 : r2;
        memcpy(new_hyperGenes[i], hyperGenes[winner], sizeof(new_hyperGenes[i]));
        new_hyper_fitness[i] = hyper_fitness[winner];
    }

    memcpy(hyperGenes[0], best_hyper, sizeof(best_hyper));
    hyper_fitness[0] = best_f;

    for(int i = 1; i < POPULATION_OF_HYPER_GA; i++){
        memcpy(hyperGenes[i], new_hyperGenes[i], sizeof(new_hyperGenes[i]));
        hyper_fitness[i] = new_hyper_fitness[i];
    }
}
