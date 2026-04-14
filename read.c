#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"
//#include "read.h"

void read(const char * filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("ファイルを開けませんでした");
    }

    
    int nodeCount = 0;
    char line[256];
    int reading_coords = 0;

    while (fgets(line, sizeof(line), file)) {
        // 改行除去
        line[strcspn(line, "\r\n")] = 0;

        if (strcmp(line, "NODE_COORD_SECTION") == 0) {
            reading_coords = 1;
            continue;
        }
        if (strcmp(line, "EOF") == 0) {
            break;
        }

        if (reading_coords) {
            int node;
            double x, y;
            if (sscanf(line, "%d %lf %lf", &node, &x, &y) == 3) {
                nodes[nodeCount].node = node;
                nodes[nodeCount].x = x;
                nodes[nodeCount].y = y;
                nodeCount++;
            }
        }
    }

    fclose(file);

}