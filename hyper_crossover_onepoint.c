#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void hyper_crossover_onepoint(){
    HyperGenes new_hyperGenes[POPULATION_OF_HYPER_GA][MAX_HYPER_GENES];
    memcpy(new_hyperGenes, hyperGenes, sizeof(new_hyperGenes));
    HyperGenes best_hyper[MAX_HYPER_GENES];
    /* initialize best as the first individual */
    memcpy(best_hyper, hyperGenes[0], sizeof(best_hyper));
    for (int i = 0; i < POPULATION_OF_HYPER_GA; i+=2)
    {
        double r = (double)rand()/RAND_MAX;
        if (hyper_crossover_rate < r){continue;}
        int crossover_point = rand()%MAX_HYPER_GENES;
        for (int j = 0; j < crossover_point; j++)
        {
            new_hyperGenes[i][j].step = hyperGenes[i+1][j].step;
            new_hyperGenes[i+1][j].step = hyperGenes[i][j].step;   
            new_hyperGenes[i][j].rate = hyperGenes[i+1][j].rate;
            new_hyperGenes[i+1][j].rate = hyperGenes[i][j].rate;   
        }
        for (int j = crossover_point; j < MAX_HYPER_GENES; j++)
        {
            new_hyperGenes[i][j].step = hyperGenes[i][j].step;
            new_hyperGenes[i+1][j].step = hyperGenes[i+1][j].step;   
            new_hyperGenes[i][j].rate = hyperGenes[i][j].rate;
            new_hyperGenes[i+1][j].rate = hyperGenes[i+1][j].rate;   
        }
        // ここで new_hyperGenes[i] と new_hyperGenes[i+1] 内で重複が起こってないか検証
        // 重複が見つかれば交叉を取りやめ，元の遺伝子に戻す
        int dup_found = 0;
        for (int a = 0; a < MAX_HYPER_GENES; a++) {
            if (!new_hyperGenes[i][a].step) continue;
            for (int b = a + 1; b < MAX_HYPER_GENES; b++) {
                if (!new_hyperGenes[i][b].step) continue;
                if (strcmp(new_hyperGenes[i][a].step, new_hyperGenes[i][b].step) == 0) {
                    dup_found = 1;
                    break;
                }
            }
            if (dup_found) break;
        }
        if (!dup_found) {
            for (int a = 0; a < MAX_HYPER_GENES; a++) {
                if (!new_hyperGenes[i+1][a].step) continue;
                for (int b = a + 1; b < MAX_HYPER_GENES; b++) {
                    if (!new_hyperGenes[i+1][b].step) continue;
                    if (strcmp(new_hyperGenes[i+1][a].step, new_hyperGenes[i+1][b].step) == 0) {
                        dup_found = 1;
                        break;
                    }
                }
                if (dup_found) break;
            }
        }
        if (dup_found) {
            /* cancel crossover for this pair: restore originals */
            memcpy(new_hyperGenes[i], hyperGenes[i], sizeof(new_hyperGenes[i]));
            memcpy(new_hyperGenes[i+1], hyperGenes[i+1], sizeof(new_hyperGenes[i+1]));
        }
    }
    memcpy(hyperGenes[0], best_hyper, sizeof(best_hyper));

    for(int i = 1; i < POPULATION_OF_HYPER_GA; i++){
        memcpy(hyperGenes[i], new_hyperGenes[i], sizeof(new_hyperGenes[i]));
    }
       
}