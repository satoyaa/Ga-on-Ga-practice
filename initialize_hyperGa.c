#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void initialize_hyperGA(){

    //初期化
    for(int i=0; i<POPULATION_OF_HYPER_GA; i++){
        for(int j=0;j<MAX_HYPER_GENES; j++){
            hyperGenes[i][j].step = NULL;
            hyperGenes[i][j].rate = -1.0;
        }
    }

    for(int i=0; i < POPULATION_OF_HYPER_GA; i++){
        int hyper_genes_length = rand()%MAX_HYPER_GENES;
        int hyper_genes_index = 0;
        while(1)
        {
            int flag = 0;
            int index = rand()%MAX_HYPER_GENES;
            float rate = (float)rand()/RAND_MAX;
            for (int j = 0; j < hyper_genes_index + 1; j++)
            {
                if (!hyperGenes[i][j].step)
                {
                    break;
                }
                if (strcmp(steps[index], hyperGenes[i][j].step) == 0){
                    
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                continue;
            }
            hyperGenes[i][hyper_genes_index].step = steps[index];
            hyperGenes[i][hyper_genes_index].rate = rate;
            hyper_genes_index++;
            if (hyper_genes_index >= hyper_genes_length)
            {
                break;
            }
        }    
    }
}