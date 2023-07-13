#include <stdio.h>
#include <stdlib.h>

/*
Siano G1 e G2 due grafi orientati e pesati (con pesi interi positivi) di 0,1,...,n-1 vertici, implementati entrambi con liste di adiacenza.
Scrivere una funzione in C che presi in input (da tastiera) G1, G2 e una lista L doppiamente puntata e non circolare di valori interi, faccia l'unione dei due grafi
in un grafo G3 e modifichi L nel modo seguente. Un arco (i,j) con peso p sarà aggiunto al grafo G3 se:
	- l'arco (i,j) è presente in almeno uno tra G1 e G2 con pesi rispettivamente p1 e p2 e p = p1+p2
	- se p è presente in L, allora sarà rimosso da L
	
Scrivere una funzione che permetta di creare da tastiera G1, G2 e L e di stamparli prima e dopo l'applicazione della funzione.
Bonus: +2 punti la funzione ha complessità quadratica nel numero dei vertici di G1 e G2.
*/

struct nodo {
    struct nodo * next;
    int elemento;
};

typedef struct edge {

    int peso; //eventualmente il peso
    int key;
    struct edge * next;

}edge;

typedef struct graph {

    edge ** adj;
    int n_vertex;

}graph;

//funzioni elementari sul grafo
graph * createGraph(graph * G, int num_vertex); //funzione che crea e inizializza il grafo 
void addArco(graph * G, int start, int dest, int peso); //funzione che aggiunge un arco
void deleteArco(graph * G, int start, int to_delete); //funzione che elimina un arco (quella facile)
void deleteVertex(graph *G, int vertex_to_delete); //funzione che elimina un vertice (quella difficile)
void printGraph(graph * G);
graph * unione(graph * G1, graph * G2, int p);


int main() {


    struct nodo * head = NULL;
   
    graph* G = NULL;
    graph* G2 = NULL;
    graph* G3 = NULL;
    

    int n_vert = 0;
    int n_archi = 0, n_archi2 = 0;

    printf("quanti verici vuoi inserire: ");
    scanf("%d", &n_vert);

    //creo il grafo passando il numero di vertici che avrà
    G = createGraph(G, n_vert);
    G2 = createGraph(G2, 3); //G2 3 vertici

    printf("quanti archi vuoi inserire in G1: ");
    scanf("%d", &n_archi);

    
    for(int i = 0; i < n_archi; i++) {
        int start, dest, peso;
        printf("start:");
        scanf("%d", &start);

        printf("dest:");
        scanf("%d", &dest);

        printf("peso:");
        scanf("%d", &peso);

        addArco(G, start, dest, peso);
    }
    printf("G1:\n");
    printGraph(G);



    printf("quanti archi vuoi inserire in G2: ");
    scanf("%d", &n_archi2);

    for(int i = 0; i < n_archi2; i++) {
        int start, dest, peso;
        printf("start:");
        scanf("%d", &start);

        printf("dest:");
        scanf("%d", &dest);

        printf("peso:");
        scanf("%d", &peso);

        addArco(G2, start, dest, peso);
    }


    printf("\nG2:\n");
    printGraph(G2);


    printf("\nunisco in G3\n");

    G3 = unione(G, G2, 10);
    
    printf("\nG3:\n");
    printGraph(G3);

    return 0;
}


graph * createGraph(graph * G, int num_vertex) {
    if(num_vertex < 0) {
        perror("numero vertici non valido");
        exit(1);
    }

    if(num_vertex == 0) {
        return NULL;
    }


    if(G == NULL) {
        G = (graph *) malloc(sizeof(graph));
        
        if(G){
            G->n_vertex = num_vertex;
            G->adj = (edge **) malloc(num_vertex * sizeof(edge));
            if(G->adj) {

                for(int i = 0; i < num_vertex; i++) {
                    G->adj[i] = NULL;
                }

            }
            else{
                perror("impossibile allocare liste di adiacenza");
                exit(1);
            }
        }
        else {
            perror("impossibile allocare grafo");
            exit(1);
        }

    }

    return G;
}

void addArco(graph * G, int start, int dest, int peso) {
    if(!G || start < 0 || start >= G->n_vertex || dest < 0 || dest >= G->n_vertex || peso < 0) {
        printf("parametri non validi\n");
        return;
    }

    //ci accertiamo che non esista gia
    edge * scorri = G->adj[start];
    while(scorri){
        if(scorri->key == dest) {
            printf("arco gia esistente\n");
            return;
        }
        scorri = scorri->next;
    }



    //creiamo il nostro nuovo nodo dest
    edge * newNodo = (edge *) malloc(sizeof(edge));
    if(newNodo) {
            newNodo->key = dest;
            newNodo->peso = peso;
            newNodo->next = NULL;
            
            if(!G->adj[start]) {
                G->adj[start] = newNodo;
                return;
            }

            scorri = G->adj[start];
            while(scorri->next) {
                scorri = scorri->next;
            }
            scorri->next = newNodo;
    }

}



void printGraph(graph * G) {
    
    for(int i = 0; i < G->n_vertex; i++) {
        edge * scorri = G->adj[i];
        printf("lista di %d: ", i);
        while(scorri){
            printf("%d -> ", scorri->key);
            scorri = scorri->next;
        }
        printf("NULL\n\n");
    }

}


void deleteArco(graph * G, int start, int to_delete) {

    if(!G || start < 0 || start >= G->n_vertex || to_delete < 0 || to_delete >= G->n_vertex) {
        printf("parametri non validi\n");
        return;
    }

    if(G->adj[start]->key == to_delete) {
        //manca la free
        G->adj[start] = G->adj[start]->next;
        return;
    }


    edge * scorri = G->adj[start];
    while(scorri) {
        if(scorri->key == to_delete) {
            edge * tmp = scorri;
            scorri = scorri->next;
            free(tmp);
        }
        scorri = scorri->next;
    }

}

graph * unione(graph * G1, graph * G2, int p) {
    int n_max = 0;

    if (G1->n_vertex >= G2->n_vertex) {
        n_max = G1->n_vertex;
    } else {
        n_max = G2->n_vertex;
    }

    graph * G3 = NULL;
    G3 = createGraph(G3, n_max); // Crea G3 con il numero massimo di vertici

    edge *scorri = NULL, *scorri2 = NULL;

    for (int i = 0; i < G1->n_vertex; i++) {
    	
    	for (int j = 0; j < G1->n_vertex; j++) {

	        scorri = G1->adj[i];
	        scorri2 = G2->adj[j];
	
	        if (scorri == NULL) {
	            if (scorri2 != NULL) {
	                while (scorri2) {
	                    if (p == scorri2->peso) {
	                        addArco(G3, j, scorri2->key, scorri2->peso);
	                    }
	                    scorri2 = scorri2->next;
	                }
	            }
	        } else if (scorri2 == NULL) {
	            if (scorri != NULL) {
	                while (scorri) {
	                    if (p == scorri->peso) {
	                        addArco(G3, i, scorri->key, scorri->peso);
	                    }
	                    scorri = scorri->next;
	                }
	            }
	        } else {
	            while (scorri) {
	                while (scorri2) {
	                    if (p == (scorri->peso + scorri2->peso)) {
	                        addArco(G3, i, scorri->key, scorri->peso);
	                        addArco(G3, j, scorri2->key, scorri2->peso);
	                    }
	                    scorri2 = scorri2->next;
	                }
	                scorri = scorri->next;
	            }
	        }
		}
    }

    return G3;
}




//Con intersezione
/*
graph* funzione_lezione(struct graph* G1, struct graph* G2, struct nodo** testa, int p) {
    int i = 0;
    int gmax;
    struct edge* g1, *g2;
    
    // Ottiene la grandezza massima tra i due grafi per darla al grafo risultante
    if (G1->num_vertex < G2->num_vertex) {
        gmax = G1->num_vertex;
    } 
    else {
        gmax = G2->num_vertex;
    }
    
    // Crea il grafo per l'intersezione
    graph* G = createGraph(gmax);
    
    // Effettua l'intersezione tra i due grafi nel terzo se la somma dei pesi è quella data in input
    while (i < gmax) {
        g1 = G1->adj[i];
        g2 = G2->adj[i];

        while (g1 != NULL) {
            while (g2 != NULL) {
                if (p == (g1->peso + g2->peso) && g1->key == g2->key) {
                    addArco(G, i, g1->key, g1->peso);
                }
                g2 = g2->next;
            }
            g1 = g1->next;
        }
        
        i++;
    }
    
    // Elimina un nodo della lista con valore p
    // Elimina il nodo se si trova in testa
    if ((*testa)->elem == p) {
        struct nodo* succ = *testa;
        *testa = (*testa)->next;
        free(succ);
    }
    else {
        struct nodo* scorri = *testa;
        
        while (scorri && scorri->next) {
            if (scorri->next->elem == p) {
                struct nodo* tmp = scorri->next;
                scorri->next = scorri->next->next;
                free(tmp);
            }
            else 
                scorri = scorri->next;
            
        }
    }
        
    return G;
}
*/


/*
//Con differenza
graph* funzione_lezione(struct graph* G1, struct graph* G2, struct nodo** testa, int p) {
    int i = 0;
    int gmax;
    struct edge* g1, *g2;
    
    // Ottiene la grandezza massima tra i due grafi per darla al grafo risultante
    if (G1->num_vertex < G2->num_vertex) {
        gmax = G2->num_vertex;
    } 
    else {
        gmax = G1->num_vertex;
    }
    
    // Crea il grafo per la differenza
    graph* G = createGraph(gmax);
    
    // Effettua la differenza tra i due grafi nel terzo se la somma dei pesi è diversa da quella data in input
    while (i < gmax) {
        g1 = G1->adj[i];
        g2 = G2->adj[i];

        while (g1 != NULL) {
            int trovato = 0;
            
            while (g2 != NULL) {
                if (p == (g1->peso + g2->peso) && g1->key == g2->key) {
                    trovato = 1;
                    break;
                }
                g2 = g2->next;
            }
            
            if (!trovato) {
                addArco(G, i, g1->key, g1->peso);
            }
            
            g1 = g1->next;
        }
        
        i++;
    }
    
    // Elimina un nodo della lista con valore p
    // Elimina il nodo se si trova in testa
    if ((*testa)->elem == p) {
        struct nodo* succ = *testa;
        *testa = (*testa)->next;
        free(succ);
    }
    else {
        struct nodo* scorri = *testa;
        
        while (scorri && scorri->next) {
            if (scorri->next->elem == p) {
                struct nodo* tmp = scorri->next;
                scorri->next = scorri->next->next;
                free(tmp);
            }
            else 
                scorri = scorri->next;
            
        }
    }
        
    return G;
}

*/


