#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "extern.h"
Node nodes[MAX_NODES];
int genes[POPULATION][MAX_NODES];
HyperGenes hyperGenes[POPULATION_OF_HYPER_GA][MAX_HYPER_GENES];
double best = INFINITY;
double hyper_best = INFINITY;
double fitness[POPULATION];
double best_fitness[LOOP];
double hyper_fitness[POPULATION_OF_HYPER_GA];
double crossover_rate;
double mutation_rate;
double hyper_mutation_rate = 0.2;
double hyper_crossover_rate = 0.7;
char const *steps[MAX_HYPER_GENES] = {"tournament_selection", "roulette_selection", "pmx", "swap", "reverse"};



void ga(int loop){

    best = INFINITY;
    //srand((unsigned int)time(NULL));
    srand(loop);
    initialize();
    //初期化の中身を表示
    
    calc_fitness();
    for(int i=0;i < MAX_ITERATION;i++){
        selection_tournament();          // トーナメント選択
        //selection_roulette();             // ルーレット選択
        //crossover_pmx();          // PMX交叉
        //mutation_reverse();           // 反転突然変異
        mutation_rate = 0.18721;
        mutation_reverse();
        mutation_rate = 0.145848;
        mutation_swap();
        mutation_rate = 0.397778;
        mutation_reverse();
        calc_fitness();// 適応度計算
    }
    // 現世代の最良個体を算出
    for (int j = 0; j < POPULATION; j++) {
        if (fitness[j] < best) {
            best = fitness[j];
        }
    }
    //printf("best:%f\n",best);
}

void aline_hyperGenes(){
    for(int i=0; i < POPULATION_OF_HYPER_GA; i++){
        int pivot = 0;
        for(int j=0;j<MAX_HYPER_GENES; j++){
            if(hyperGenes[i][j].step == NULL){
                break;
            }
            if(strstr(hyperGenes[i][j].step, "selection") != NULL){
                HyperGenes temp;
                temp.step = hyperGenes[i][j].step;
                temp.rate = hyperGenes[i][j].rate;
                for (int k = pivot; k < j; k++)
                {
                    hyperGenes[i][k+1].step = hyperGenes[i][k].step;
                    hyperGenes[i][k+1].rate = hyperGenes[i][k].rate;
                }
                hyperGenes[i][pivot].step=temp.step;
                hyperGenes[i][pivot].rate=temp.rate;
            }
        }
    }    
}

void hyperGa(){
    srand((unsigned int)time(NULL));
    const char* filename = "Iteration.txt";
    FILE* fp = fopen(filename, "w"); 
    char line[256];
    int hyper_individual = 0;
    initialize_hyperGA();

    hyper_calc_fitness();
    
    for (int i = 0; i < MAX_ITERATION_OF_HYPER_GA; i++)
    {
        //srand(1);
        
        printf("iteration:%d. ", i);
        hyper_selection_tournament();
        printf("selection done. ");
        

        hyper_mutation_replacement();
        printf("mutation done. ");

        hyper_crossover_onepoint();

        printf("crossover done. ");

        aline_hyperGenes();
        hyper_calc_fitness();
        printf("fitness done. best is %f. \n", hyper_fitness[0]);
        snprintf(line, sizeof(line), "%f\n", hyper_fitness[0]);
        fprintf(fp, "%s", line);
    }
    for (int j = 0; j < POPULATION_OF_HYPER_GA; j++) {
        if (hyper_fitness[j] < hyper_best) {
            hyper_best = hyper_fitness[j];
            hyper_individual = j;
        }
    }
    printf("hyper_best:%f\n", hyper_best);

    snprintf(line, sizeof(line), "%f\n", hyper_best);
    fprintf(fp, "%s", line);
    fclose(fp);

    //　最適解も保存
    const char* filenameAns = "Answer.txt";
    FILE* fpAns = fopen(filenameAns, "w"); 
    char lineAns[256];
    for (int j = 0; j < MAX_HYPER_GENES; j++) {
        if (hyperGenes[hyper_individual][j].step) {
            snprintf(lineAns, sizeof(lineAns), "%s %f\n", hyperGenes[hyper_individual][j].step, hyperGenes[hyper_individual][j].rate);
            fprintf(fpAns, "%s", lineAns);
        }
    }
    fclose(fpAns);

    // hyper_individualの遺伝子を表示
    printf("Best HyperGenes: ");
    for (int j = 0; j < MAX_HYPER_GENES; j++) {
        if (hyperGenes[hyper_individual][j].step) {
            printf("%s %f ", hyperGenes[hyper_individual][j].step, hyperGenes[hyper_individual][j].rate);
        }
    }
    //初期化の中身を見る
    /*
    for(int i=0; i < POPULATION_OF_HYPER_GA; i++){
        printf("HyperGenes %d: ", i);
        for(int j=0;j<MAX_HYPER_GENES; j++){
            printf("%s %f ", hyperGenes[i][j].step, hyperGenes[i][j].rate);
        }
        printf("\n");
    }*/
    
}

void gaTest(){
    double sum_ga_fitness = 0.0;
    double best_of_best = INFINITY;
    for (int i = 0; i < LOOP; i++)
    {
        ga(i);
        sum_ga_fitness += best;
        best_fitness[i] = best;
        if(best < best_of_best){
            best_of_best = best;
        }
    }
    double average_ga_fitness = sum_ga_fitness / LOOP;
    //分散を計算
    double sum_ga_fitness_squared_diff = 0.0;
    for (int i = 0; i < LOOP; i++)
    {
        sum_ga_fitness_squared_diff += (best_fitness[i] - average_ga_fitness) * (best_fitness[i] - average_ga_fitness);   
    }
    printf("Average GA Fitness: %f\n", average_ga_fitness);
    printf("Variance GA Fitness: %f\n", sum_ga_fitness_squared_diff / LOOP);
    printf("Standard Deviation GA Fitness: %f\n", sqrt(sum_ga_fitness_squared_diff / LOOP));
    printf("best:%f\n",best_of_best);
}

int main() {

    
    read("eil51.tsp");

    //gaTest();
    //実行時間を計測
    clock_t start = clock();
    hyperGa();
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    //printf("Elapsed time: %f seconds\n", elapsed);
    return 0;
}