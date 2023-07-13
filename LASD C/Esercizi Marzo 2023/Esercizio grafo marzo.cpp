#include <stdio.h>
#include <stdlib.h>

struct edge{
    int info;
    int peso;
    struct edge* next;
};

struct vertex {
    int value;
    struct edge* edges;
};

struct graph{
    int num_v;
    struct vertex* vertices;
};

void g_add(struct graph* G, int u, int v, int peso);
struct graph* crea_grafo(int n_elem);
void stampa_grafo(struct graph* G);
struct graph* graphDifference(struct graph* graph1, struct graph* graph2);
int isVertexPresent(struct graph* graph, int value);
int isEdgePresent(struct edge* edges, int dest, int peso);


int main(){
    struct graph* grafo1, *grafo2, *grafo3;
    
    grafo1 = crea_grafo(4);
    grafo2 = crea_grafo(3);

    g_add(grafo1, 0, 1, 5);
    g_add(grafo1, 0, 2, 3);
    g_add(grafo1, 1, 2, 2);
    g_add(grafo1, 1, 0, 1);
    g_add(grafo1, 2, 1, 3);
    g_add(grafo1, 3, 2, 5);
    
    g_add(grafo2, 0, 1, 4);
    g_add(grafo2, 0, 2, 6);
    g_add(grafo2, 1, 2, 3);
    g_add(grafo2, 2, 1, 3);

    
    stampa_grafo(grafo1);
    printf("\n");
    stampa_grafo(grafo2);
    
    grafo3 = graphDifference(grafo1, grafo2);
    stampa_grafo(grafo3);

    return 0;
}

struct graph* crea_grafo(int n){
    struct graph* G = (struct graph*)malloc(sizeof(struct graph));
    if (G == NULL){
        printf("ERRORE: impossibile allocare memoria per il grafo\n");
        return NULL;
    }

    G->num_v = n;
    G->vertices = (struct vertex*)malloc(n * sizeof(struct vertex));
    if (G->vertices == NULL){
        printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
        free(G);
        return NULL;
    }

    for (int i = 0; i < n; i++){
        G->vertices[i].value = i;
        G->vertices[i].edges = NULL;
    }

    return G;
}

void g_add(struct graph* G, int u, int v, int peso){
    struct edge* new1 = (struct edge*)malloc(sizeof(struct edge));
    if (new1 == NULL){
        printf("ERRORE: impossibile allocare memoria \n");
        return;
    }

    new1->info = v;
    new1->peso = peso;
    new1->next = NULL;

    struct edge* edges = G->vertices[u].edges;
    if (edges == NULL){
        G->vertices[u].edges = new1;
    }
    else{
        struct edge* e = edges;
        while (e->next != NULL){
            e = e->next;
        }
        e->next = new1;
    }
}

void stampa_grafo(struct graph* G){
    printf("\nil grafo ha %d vertici\n", G->num_v);
    for (int i = 0; i < G->num_v; i++){
        printf("nodo %d\n", G->vertices[i].value);
        struct edge* e = G->vertices[i].edges;
        while (e != NULL){
            printf("->%d (peso: %d)\n", e->info, e->peso);
            e = e->next;
        }
        printf("\n");
    }
}

struct graph* graphDifference(struct graph* graph1, struct graph* graph2){
    int maxVertices = graph1->num_v;
    if (graph2->num_v < maxVertices){
        maxVertices = graph2->num_v;
    }

    struct graph* diffGraph = crea_grafo(maxVertices);

    // Verifica i vertici presenti in graph1 che non sono presenti in graph2
    for (int i = 0; i < maxVertices; i++){
        if (!isVertexPresent(graph2, graph1->vertices[i].value)){
            g_add(diffGraph, i, graph1->vertices[i].value, 0);
        }
    }

    return diffGraph;
}

int isVertexPresent(struct graph* graph, int value){
    for (int i = 0; i < graph->num_v; i++){
        if (graph->vertices[i].value == value){
            return 1;
        }
    }
    return 0;
}

int isEdgePresent(struct edge* edges, int dest, int peso){
    struct edge* currentNode = edges;
    while (currentNode != NULL){
        if (currentNode->info == dest && currentNode->peso == peso){
            return 1;
        }
        currentNode = currentNode->next;
    }
    return 0;
}

