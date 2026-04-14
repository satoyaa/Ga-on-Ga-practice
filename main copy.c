#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "extern.h"
Node nodes[MAX_NODES];
int genes[population][MAX_NODES];
int count[population];
double variety_rate[population];
double best = INFINITY;
double fitness[population];
double crossover_rates[3];
double mutation_rates[3];
double crossover_rate;
double mutation_rate;
double best_crossover_rate;
double best_mutation_rate;
double best2_crossover_rate;
double best2_mutation_rate;


void ga(){
    initialize();

    calc_fitness();
    for(int i=0;i < max_iteration;i++){
        selection();          // トーナメント選択
        crossover();          // PMX交叉
        mutation();           // 反転交叉
        calc_fitness();// 適応度計算
    }
    // 現世代の最良個体を算出
    for (int j = 0; j < population; j++) {
        if (fitness[j] < best) {
            best = fitness[j];
        }
    }
    //printf("best:%f\n",best);
}

void turning(const char* filename){
    double bset_fitness = INFINITY;
    best_mutation_rate=0;
    best_crossover_rate=0;
    FILE* fp = fopen(filename, "w"); 
    char line[256];
    for(int i = 0; i < 3; i++){
        crossover_rate = crossover_rates[i];
        if(crossover_rate == -1){continue;}
        for(int j = 0; j < 3 ;j++){
            mutation_rate = mutation_rates[j];
            if(mutation_rate == -1){continue;}
            double sum_best = 0;
            char line[256];
            for(int k=0;k<loop;k++){
                best = INFINITY;
                ga();
                sum_best = sum_best +best;
            }
            printf("crossover:%f,mutation:%f,best:%f\n",crossover_rate,mutation_rate,sum_best/loop);
            snprintf(line, sizeof(line), "%f %f %f\n",crossover_rate,mutation_rate,sum_best/loop);
            fprintf(fp, "%s", line);
            if(sum_best<bset_fitness){
                best2_crossover_rate=best_crossover_rate;
                best2_mutation_rate=best_mutation_rate;
                best_crossover_rate=crossover_rate;
                best_mutation_rate=mutation_rate;
                bset_fitness=sum_best;}
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int main() {

    
    read("eil51.tsp");

    const char* filename = "testa.txt";
    const char* varfilename = "aaaaaa.txt";
    FILE* varfp = fopen(varfilename, "w"); 

    if (varfp == NULL) {
        perror("ファイルオープンに失敗しまし");
        return 1;
    }

    double bset_fitness = INFINITY;
    FILE* fp = fopen(filename, "w"); 
    double rates[] = {0, 0.001, 0.002, 0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1.0};
    for(int i = 0; i < 11; i++){
        crossover_rate = i *0.1;
        for(int j = 0;j<11;j++){
            mutation_rate = rates[j];
            double sum_best = 0;
            char line[256];
            for(int k=0;k<loop;k++){
                best = INFINITY;
                ga();
                sum_best = sum_best +best;
            }
            printf("crossover:%f,mutation:%f,best:%f\n",crossover_rate,mutation_rate,sum_best/loop);
            snprintf(line, sizeof(line), "%f %f %f\n",crossover_rate,mutation_rate,sum_best/loop);
            fprintf(fp, "%s", line);
            if(sum_best<bset_fitness){best_mutation_rate=mutation_rate;best_crossover_rate=crossover_rate;bset_fitness=sum_best;}
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    double biasC = 0.05;
    double biasM = 0.25;
    for (int i = 0; i < 3; i++)
    {
        printf("%f\n",best_mutation_rate+best_mutation_rate*biasM*(i-1));
        if(0<=best_crossover_rate+(biasC*(i-1))&&best_crossover_rate+(biasC*(i-1))<=1)
        {
            crossover_rates[i]=best_crossover_rate+(biasC*(i-1));
        }
        else{crossover_rates[i]=-1;}
        if(0<=best_mutation_rate+best_mutation_rate*biasM*(i-1)&&best_mutation_rate+best_mutation_rate*biasM*(i-1)<=1)
        {
            mutation_rates[i]=best_mutation_rate+best_mutation_rate*biasM*(i-1);
        }
        else{crossover_rates[i]=-1;}
    }

    char file[100];
    const char *base_name = "testa";
    const char *extension = ".txt";
    biasM = 0.25;
    for (int i = 0; i < MAX_LOOP; i++)
    {
        //実行
        sprintf(file, "%s%d%s", base_name, i, extension);
        turning(file);

        //t検定　有意差なしで終了
        if (tTest())
        {
            break;
        }
        //次の探索域を決定
        double b1 = crossover_rates[2];
        double b2 = crossover_rates[0];
        if(b1==-1){b1=crossover_rates[1];}
        if(b1==-1){b1=0;}
        if(b2==-1){b2=crossover_rates[1];}
        if(b2==-1){b2=0;}
        biasC = b1 - b2;
        biasC = biasC * 0.25;
        for (int i = 0; i < 3; i++)
        {
            if(0<=best_crossover_rate+(biasC*(i-1))&&best_crossover_rate+(biasC*(i-1))<=1)
            {
                crossover_rates[i]=best_crossover_rate+(biasC*(i-1));
            }
            else{crossover_rates[i]=-1;}
            if(0<=best_mutation_rate+best_mutation_rate*biasM*(i-1)&&best_mutation_rate+best_mutation_rate*biasM*(i-1)<=1)
            {
                mutation_rates[i]=best_mutation_rate+best_mutation_rate*biasM*(i-1);
            }
            else{crossover_rates[i]=-1;}
        }
        biasM = biasM*0.5;
    }

    printf("best crossover is %f, best mutation rate is %f\n",best_crossover_rate, best2_mutation_rate);
    
    // ファイルを閉じる
    
    fclose(varfp);
    

    /*
    for (int i = 0; i < 100; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < 51; j++) {
            printf("%d ", genes[i][j]);
        }
        printf("\n");
    }
        */
    return 0;
}