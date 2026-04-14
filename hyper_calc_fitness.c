#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "extern.h"

void select_step(int individual){
    //各個体
    
    //各遺伝子
    for (int j = 0; j < MAX_HYPER_GENES; j++)
    {
        if (!hyperGenes[individual][j].step)
        {
            break;
        }
        //一致判定を行い，ステップを選択
        if (strcmp("tournament_selection", hyperGenes[individual][j].step) == 0)
        {
            selection_tournament();
        }
        else if (strcmp("roulette_selection", hyperGenes[individual][j].step) == 0)
        {
            
            selection_roulette();
            
        }
        else if (strcmp("pmx", hyperGenes[individual][j].step) == 0)
        {
            crossover_rate = hyperGenes[individual][j].rate;
            crossover_pmx();
        }
        else if (strcmp("swap", hyperGenes[individual][j].step) == 0)
        {
            mutation_rate = hyperGenes[individual][j].rate;
            mutation_swap();
        }
        else if (strcmp("reverse", hyperGenes[individual][j].step) == 0)
        {
            mutation_rate = hyperGenes[individual][j].rate;
            mutation_reverse();
        }
    }    
}

void calc_hyper_fitness_ga(int individual){
    //ここで初期化
    srand((unsigned int)time(NULL));
    initialize();
    calc_fitness();
    best = INFINITY;
    for(int i=0;i < MAX_ITERATION;i++){
        select_step(individual);
        calc_fitness();
        
    }
    // 現世代の最良個体を算出
    for (int j = 0; j < POPULATION; j++) {
        if (fitness[j] < best) {
            best = fitness[j];
        }
    }
}

void hyper_calc_fitness(){
    for(int i=0; i<POPULATION_OF_HYPER_GA; i++){
        double sum_best_fitness = 0;
        for (int i = 0; i < LOOP; i++)
        {
            calc_hyper_fitness_ga(i);
            
            sum_best_fitness += best;
        }
        hyper_fitness[i] = sum_best_fitness / LOOP; // 平均適応度を計算
    }
}