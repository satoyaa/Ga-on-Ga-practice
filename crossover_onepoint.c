#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

void crossover_onepoint(){
    int temp[POPULATION][MAX_NODES];
    int crossover_point = rand()%MAX_NODES;
    for (int i = 0; i < POPULATION; i+=2)
    {
        double r = (double)rand()/RAND_MAX;
        if (crossover_rate < r){continue;}
        for (int j = 0; j < crossover_point; j++)
        {
            temp[i][j] = genes[i+1][j];
            temp[i+1][j] = genes[i][j];
        }
        for (int j = crossover_point; j < MAX_NODES; j++)
        {
            temp[i][j] = genes[i][j];
            temp[i+1][j] = genes[i+1][j];
        }
    }
    for (int i = 1; i < POPULATION; i++)
    {
        for (int j = 0; j < MAX_NODES; j++)
        {
            genes[i][j] = temp[i][j];
        }
    }
    
}