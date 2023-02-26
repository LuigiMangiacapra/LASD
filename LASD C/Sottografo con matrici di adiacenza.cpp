/*
Grafi con matrice di adiacenza e funzione sottografo
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100 // definisci il numero massimo di vertici

// struttura del grafo
struct Graph {
    int num_vertices;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
};

// verifica se graph1 è un sottografo di graph2
bool isSubgraph(struct Graph graph1, struct Graph graph2) {
    if (graph1.num_vertices > graph2.num_vertices) {
        return false; // il grafo 1 non può essere un sottografo del grafo 2 se ha più vertici
    }
    for (int i = 0; i < graph1.num_vertices; i++) {
        for (int j = 0; j < graph1.num_vertices; j++) {
            if (graph1.adj_matrix[i][j] == 1 && graph2.adj_matrix[i][j] == 0) {
                return false; // se un arco esiste nel grafo 1 ma non nel grafo 2, allora graph1 non è un sottografo di graph2
            }
        }
    }
    return true;
}

// esempio di utilizzo della funzione isSubgraph
int main() {
    struct Graph graph1 = {
        .num_vertices = 3,
        .adj_matrix = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
        }
    };
    struct Graph graph2 = {
        .num_vertices = 4,
        .adj_matrix = {
            {0, 1, 1, 0},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {0, 1, 1, 0}
        }
    };
    if (isSubgraph(graph1, graph2)) {
        printf("graph1 è un sottografo di graph2\n");
    } else {
        printf("graph1 non è un sottografo di graph2\n");
    }
    return 0;
}

