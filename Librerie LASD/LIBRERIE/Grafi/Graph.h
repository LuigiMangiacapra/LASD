#ifndef Graph_Graph_h
#define Graph_Graph_h
#include "List.h"

struct TGraph {
    List *adj;
    int nodes_count;
};

typedef struct TGraph* Graph;

// Inizializza un nuovo grafo
// specifica in ingresso quanti nodi vuoi nel grafo
Graph initGraph(int nodes_count);

// Crea un grafo in modo random
//
// Inserisci in nodes il numero dei nodi che vuoi nel grafo
//
// Inserisci in edges_min il numero minimo di archi
// che ogni nodo deve avere
//
// Inserisci in edges_max il numero massimo di archi
// che ogni nodo puo' avere
//
// Ritorna il nuovo grafo creato
Graph randomGraph(int nodes, int edges_min, int edges_max);

// Dealloca l'intero grafo
void freeGraph(Graph G);

// Stampa il grafo
void printGraph(Graph G);

// Aggiunge un arco, specificando sorgente,
// target e peso
void addEdge(Graph G, int source, int target, int peso);

// Rimuovi un arco specificando sorgente e target,restituisce la lista degli archi modifcata
List removeEdge(Graph G, int source, int target);

// Aggiungi un nodo
void addNode(Graph G);

// Rimuovi un nodo dal grafo, sistemando
// gli indici e riallocando la memoria
void removeNode(Graph G, int node_to_remove);
List checkListRemoval(List L, int node_to_remove);

#endif
