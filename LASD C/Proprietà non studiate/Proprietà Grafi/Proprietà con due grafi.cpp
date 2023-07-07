#include <stdio.h>
#include <stdlib.h>


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
graph* createGraph(int n); //funzione che crea e inizializza il grafo 
void addArco(graph * G, int start, int dest, int peso); //funzione che aggiunge un arco
void deleteArco(graph * G, int start, int to_delete); //funzione che elimina un arco (quella facile)
void deleteVertex(graph *G, int vertex_to_delete); //funzione che elimina un vertice (quella difficile)
void printGraph(graph * G);
graph* unione(graph* G1, graph* G2);
graph* intersezione(graph* G1, graph* G2);
graph* differenza(graph* G1, graph* G2);
void is_subgraph(graph* G1, graph* G2);

int main() {


    struct nodo * head = NULL;
   
    graph* G = NULL;
    graph* G2 = NULL;
    graph* G3 = NULL;
    graph* G4 = NULL;
    graph* G5 = NULL;

    int n_vert = 0;
    int n_archi = 0, n_archi2 = 0;

    printf("quanti verici vuoi inserire: ");
    scanf("%d", &n_vert);

    //creo il grafo passando il numero di vertici che avrà
    G = createGraph(n_vert);
    G2 = createGraph(3); //G2 3 vertici

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

    G3 = unione(G, G2);
    
    printf("\nG3:\n");
    printGraph(G3);
    
    
    printf("\ninterseco in G4\n");

    G4 = intersezione(G, G2);

	printf("\nG4:\n");
    printGraph(G4);


	printf("\ndifferenza in G5\n");

    G5 = differenza(G, G2);

	printf("\nG5:\n");
    printGraph(G5);
    
    
    printf("\nVediamo se G1 e' sottografo di G2\n");
    
    is_subgraph(G, G2);

    return 0;
}


//creazione grafo vuoto (senza le varie liste di adiacenza)
graph* createGraph(int n){//prende in input il numero di vertici per assegnarli successivamente alla struttura
	graph *G;
	int i;
	G=(graph*)malloc(sizeof(graph));//alloca memoria per il grafo
	if(G==NULL)
		printf("ERRORE: impossibile allocare memoria per il grafo\n");
	else{
		G->adj = (edge**)malloc(n*sizeof(edge*));//alloca memoria per la lista di adiacenza collegandolo al campo adj della struct del grafo
		if (G->adj==NULL) {
			printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
			free(G);//Se non è possibile allocare memoria per la lista, il grafo non ha senso di esistere
			G=NULL;//G=NULL dopo aver liberato memoria in modo tale che l'indirizzo del grafo punti su una locazione nulla
					//e non vuota
		}
		else{
			G->n_vertex=n;//assegna a G->num il numero di vertici dato in input
			for(i=0; i<n; i++)
				G->adj[i]=NULL;
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

graph* unione(graph* G1, graph* G2) {
    int n_max = 0;
    int i, j;
    edge* e;

    if (G1->n_vertex >= G2->n_vertex) {
        n_max = G1->n_vertex;
    } else {
        n_max = G2->n_vertex;
    }

    graph * G3 = NULL;
    G3 = createGraph(n_max); // Crea G3 con il numero massimo di vertici

    for(i = 0; i < G1->n_vertex; i++){
    	e = G1->adj[i];
    	while(e != NULL){
    		addArco(G3, i, e->key, e->peso);
    		e = e->next;
		}
    		
	}

	for(j = 0; j < G2->n_vertex; j++){
    	e = G2->adj[j];
    	while(e != NULL){
    		addArco(G3, j, e->key, e->peso);
    		e = e->next;
		}
    		
	}


    return G3;
}




//Con intersezione

graph* intersezione(graph* G1, graph* G2) {
    int i = 0;
    int gmin;
    struct edge* g1, *g2;
    struct edge* e, *e2;
    
    // Ottiene la grandezza massima tra i due grafi per darla al grafo risultante
    if (G1->n_vertex > G2->n_vertex) {
        gmin = G1->n_vertex;
    } 
    else {
        gmin = G2->n_vertex;
    }
    
    // Crea il grafo per l'intersezione
    graph* G3 = createGraph(gmin);
    
    for(i = 0; i < gmin; i++){
    	e = G1->adj[i];
    	
    	while(e != NULL){
    		
    		e2 = G2->adj[i];
    		while(e2 != NULL){
    			
    			if(e->key == e2->key){
    				addArco(G3, i, e->key, e->peso);
				}
				
				e2 = e2->next;
			}
    		
    		e = e->next;
		}
    		
	}

        
    return G3;
}




//Con differenza
graph* differenza(graph* G1, graph* G2) {
    int i = 0;
    int gmin;
    struct edge* g1, *g2;
    struct edge* e, *e2;
    int flag = 0;
    
    // Ottiene la grandezza massima tra i due grafi per darla al grafo risultante
    if (G1->n_vertex > G2->n_vertex) {
        gmin = G1->n_vertex;
    } 
    else {
        gmin = G2->n_vertex;
    }
    
    // Crea il grafo per l'intersezione
    graph* G3 = createGraph(gmin);
    
    for(i = 0; i < gmin; i++){
    	flag = 0;
    	e = G1->adj[i];
    	
    	while(e != NULL){
    		flag = 0;
    		
    		e2 = G2->adj[i];
    		while(e2 != NULL){
    			
    			if(e->key == e2->key){
    				flag = 1;
    				break;
				}
				
				e2 = e2->next;
			}
			
			if(flag == 0){
				addArco(G3, i, e->key, e->peso);
			}
    		
    		e = e->next;
		}
    	
    	e2 = G2->adj[i];
    	while(e2 != NULL){
    		flag = 0;
    		
    		e = G1->adj[i];
    		while(e != NULL){
    			
    			if(e->key == e2->key){
    				flag = 1;
    				break;
				}
				
				e = e->next;
			}
			
			if(flag == 0){
				addArco(G3, i, e2->key, e2->peso);
			}
    		
    		e2 = e2->next;
		}
	}

        
    return G3;
}


void is_subgraph(graph* G1, graph* G2){
    int i = 0;
    int flag = 0;

    // Ottiene la grandezza massima tra i due grafi per darla al grafo risultante
    if (G1->n_vertex > G2->n_vertex) {
        printf("G1 non e' sottografo di G2\n");
        return;
    }

    for(i = 0; i < G1->n_vertex; i++){
        flag = 0;
        struct edge* e = G1->adj[i];
        
        while(e != NULL){
            int found = 0;
            struct edge* e2 = G2->adj[i];

            while(e2 != NULL){
                if(e->key == e2->key){
                    found = 1;
                    break;
                }
                
                e2 = e2->next;
            }
            
            if(found == 0){
                flag = 1;
                break;
            }
            
            e = e->next;
        }
        
        if(flag == 1){
            break;
        }
    }

    if(flag == 0){
        printf("G1 e' sottografo di G2\n");
    } else {
        printf("G1 non e' sottografo di G2\n");
    }
}





