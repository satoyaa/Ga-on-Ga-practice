#ifndef EXTERN_H
#define EXTERN_H

#define MAX_NODES 51
#define MAX_ITERATION 1000
#define MAX_ITERATION_OF_HYPER_GA 50
#define POPULATION 100
#define POPULATION_OF_HYPER_GA 100
#define MAX_LOOP 10
#define SAMPLE_SIZE 100
#define Critical_value 1.65258578361785 //自由度198の境界値
#define LOOP 30 //標本数
#define MAX_HYPER_GENES 5




typedef struct {
    int node;
    double x;
    double y;
} Node;

typedef struct
{
    const char *step;
    float rate;
} HyperGenes;


extern Node nodes[MAX_NODES];  // 構造体配列の外部宣言
extern int genes[POPULATION][MAX_NODES]; 
extern HyperGenes hyperGenes[POPULATION][MAX_HYPER_GENES];
extern double fitness[POPULATION];
extern double hyper_fitness[POPULATION_OF_HYPER_GA];
extern double crossover_rates[3];
extern double mutation_rates[3];
extern char const *steps[MAX_HYPER_GENES];
extern void read(const char * filename);
extern void initialize();
extern void initialize_hyperGA();
extern void selection_tournament();
extern void hyper_selection_tournament();
extern void selection_roulette();
extern void calc_fitness();
extern void hyper_calc_fitness();
extern void crossover_pmx();
extern void mutation_reverse();
extern void mutation_swap();
extern void hyper_mutation_replacement();
extern void hyper_crossover_onepoint();
extern double crossover_rate;
extern double mutation_rate;
extern double hyper_mutation_rate;
extern double hyper_crossover_rate;
extern double best_crossover_rate;
extern double best_mutation_rate;
extern double best2_crossover_rate;
extern double best2_mutation_rate;
extern double best;
extern double hyper_best;
extern int count[POPULATION];
extern double variety_rate[POPULATION];

#endif

