#ifndef ABR_Tree_h
#define ABR_Tree_h

struct TTree {
    int info;
    struct TTree* sx;
    struct TTree* dx;
};

typedef struct TTree* Tree;

// Inserisce un nodo nell'albero BST
Tree insertNodeTree(Tree T, int info);

// Inizializza un nuovo nodo
Tree initNode(int info);

// Crea un albero random, come index bisogna specificare
// il numero dei nodi desiderato nell'albero
Tree randomTree(int index);

// Esegue una visita In Order sull'albero T
void inOrder(Tree T);

// Esegue una visita in Pre Order sull'albero T
void preOrder(Tree T);

// Esegue una visita in Post Order sull'albero T
void postOrder(Tree T);

void freeTree(Tree );
#endif
