#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "extern.h"

int calc_distance(int i, int j){
    double x1 = nodes[i].x;
    double x2 = nodes[j].x;
    double y1 = nodes[i].y;
    double y2 = nodes[j].y;

    double dx = x1-x2;
    double dy = y1-y2;
    return sqrt(dx*dx + dy*dy);
}

void calc_fitness(){
    double sum_fitness;
    double distance;
    for(int i=0; i<POPULATION; i++){

        sum_fitness = 0;
        for(int j=0;j<MAX_NODES-1;j++){
            distance = calc_distance(genes[i][j],genes[i][j+1]);
            sum_fitness = sum_fitness + distance;
            //printf("distance:%f\n",distance);
        }
        fitness[i] = sum_fitness;
    }
}