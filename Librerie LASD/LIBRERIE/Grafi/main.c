#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    
    // Creo un grafo in modo random,
    // specificando che deve avere 20 nodi e almeno 5 archi
    // con un massimo di 25
    Graph G = randomGraph(20,8,10);
    printGraph(G);
    // insert code here...
    printf("Hello, World!\n");
    freeGraph(G);
    return 0;
}

