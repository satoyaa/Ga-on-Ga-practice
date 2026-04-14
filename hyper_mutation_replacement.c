#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void hyper_mutation_replacement(){
    HyperGenes new_hyperGenes[POPULATION_OF_HYPER_GA][MAX_HYPER_GENES];
    for (int i = 1; i < POPULATION_OF_HYPER_GA; i++)
    {
        for (int j = 0; j < MAX_HYPER_GENES; j++)
        { 
            double r = (double)rand()/RAND_MAX;
            if (hyper_mutation_rate < r){continue;}
            
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
                int r = rand()%MAX_HYPER_GENES+1;
                if(r == 1 && hyper_genes_index!=0){
                    hyperGenes[i][hyper_genes_index].step = NULL;
                    hyperGenes[i][hyper_genes_index].rate = -1.0;
                }else{
                    hyperGenes[i][hyper_genes_index].step = steps[index];
                    hyperGenes[i][hyper_genes_index].rate = rate;
                }
                hyper_genes_index++;
                if (hyper_genes_index >= hyper_genes_length)
                {
                    break;
                }
            }    
            }
        
    }
    

}