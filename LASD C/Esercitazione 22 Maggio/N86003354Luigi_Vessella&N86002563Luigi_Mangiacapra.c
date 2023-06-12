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
	int elem;
	struct nodo* next;	
};

typedef struct edge {
	int peso;
	int key;
	struct edge* next;
}edge;

typedef struct graph {
	int num_vertex;
	edge** adj;
}graph;

struct nodo * insertHead(struct nodo * head, int num);
void printList(struct nodo * head);
graph* createGraph(int n);
void addArco(graph* G, int start, int dest, int peso);
void printGraph(graph* G);
graph* funzione_lezione(struct graph* G1, struct graph* G2, struct nodo** testa, int p);

int main() {
    struct nodo* head = NULL;
    int dimensione_lista, i = 0;
    graph* G3 = NULL;
    int part, arrivo, peso;

    printf("inserisci dimensione lista:");
    scanf("%d", &dimensione_lista);

    for (i = 0; i < dimensione_lista; i++) {
        int numero;
        printf("inserisci lista:");
        scanf("%d", &numero);
        head = insertHead(head, numero);
    }

    printList(head);
    
    //PRIMO GRAFO
    int numero_v;
    int numero_archi1;

	//Creazione grafo G1
    printf("inserisci numero vertici per il primo grafo:");
    scanf("%d", &numero_v);
    graph* G1 = NULL;
    G1 = createGraph(numero_v);
    
    //Inserimento archi nel grafo G1
    printf("inserisci numero archi per il primo grafo:");
    scanf("%d", &numero_archi1);
    while(numero_archi1 != 0){
    	printf("Aggiungi vertice di partenza:");
    	scanf("%d", &part);
    	printf("Aggiungi vertice di arrivo:");
    	scanf("%d", &arrivo);
    	printf("Aggiungi peso:");
    	scanf("%d", &peso);
    	addArco(G1, part, arrivo, peso);
    	numero_archi1--;
    	
	}
	
	//Stampa grafo G1
    printf("Grafo G1\n");
    printGraph(G1);


	printf("\n");

	
	
	//SECONDO GRAFO
	int numero_v2;
	int numero_archi2;
	
	//Creazione grafo G2
	printf("inserisci numero vertici per il secondo grafo:");
    scanf("%d", &numero_v2);
    graph* G2 = NULL;
    G2 = createGraph(numero_v2);
    
    //Inserimento archi nel grafo G2
    printf("inserisci numero archi per il secondo grafo:");
    scanf("%d", &numero_archi2);
    
    while(numero_archi2 != 0){
    	printf("Aggiungi vertice di partenza:");
    	scanf("%d", &part);
    	printf("Aggiungi vertice di arrivo:");
    	scanf("%d", &arrivo);
    	printf("Aggiungi peso:");
    	scanf("%d", &peso);
    	addArco(G2, part, arrivo, peso);
    	numero_archi2--;
    	
	}
	
	//Stampa del grafo G2
    printf("Grafo G2\n");
    printGraph(G2);


	//ESERCIZIO
    int p;
    printf("inserisci valore p: ");
    scanf("%d", &p);

    G3 = funzione_lezione(G1, G2, &head, p);

    printf("Grafo G3:\n");
    printGraph(G3);

    printf("Lista dopo la modifica:\n");
    printList(head);

    return 0;
}

struct nodo* insertHead(struct nodo* head, int num){
	struct nodo* newNodo = (struct nodo* )malloc(sizeof(struct nodo));

	
	if(newNodo != NULL) {
		newNodo->elem = num;
		newNodo->next = NULL;
		
		if(head == NULL) 
			head = newNodo;
		else {
			newNodo->next = head;
			head = newNodo;
		}
	}
	
	return head;
	
}


void printList(struct nodo* head) {
	while(head) {
		printf("%d->", head->elem);
		head = head->next;
	}
	printf("NULL\n");
}


graph* createGraph(int n) {
	graph* G = (graph*)malloc (sizeof(graph));
	int i = 0;
	if(G) {
		G->adj = (edge**) malloc(n * sizeof(edge*));
		if(G->adj) {
			G->num_vertex = n;
			while(i < n) {
				G->adj[i] = NULL;
				i++;
			}
		}
		else{
			perror("errore adj");
			exit(1);
		}
		
	}	
	else {
		perror("errore  malloc");
		exit(1);
	}
	
	return G;
}


void addArco(graph* G, int start, int dest, int peso) {
	
	//Controllo presenza del vertice di partenza
	if(start > G->num_vertex || start < 0 || dest > G->num_vertex || dest < 0) {
		printf("vertici fuori range\n");
		return;
	}
	
	//Creazione del vertice da inserire
	edge* newVertex = (edge* )malloc(sizeof(edge));
	newVertex->key = dest;
	newVertex->peso = peso;
	newVertex->next = NULL;
	
	
	// Controllo se l'arco è già presente
    edge* scorri = G->adj[start];
    while (scorri != NULL) {
        if (scorri->key == dest) {
            printf("Arco duplicato: (%d, %d)\n", start, dest);
            free(newVertex); // Liberare la memoria allocata per il nuovo arco
            return;
        }
        scorri = scorri->next;
    }
	
    // Se il vertice di partenza non ha archi, aggiungo il nuovo arco come primo elemento
	if (G->adj[start] == NULL){ //start non ha archi
		G->adj[start] = newVertex;
	}	
	else {
		//Aggiunta dell'arco in coda
		edge* scorri = G->adj[start];
		
		while(scorri->next != NULL) {
			scorri = scorri->next;
		}
		scorri->next = newVertex;
	}
	
	
}

void printGraph(graph* G){
	int i = 0;
	for(i = 0; i < G->num_vertex; i++) {
		struct edge * scorri = G->adj[i];
		printf("%d:", i);
		while(scorri != NULL) {
			printf("|%d| ", scorri->key);
			scorri = scorri->next;
		}
		printf("\n");
	}
}


graph* funzione_lezione(struct graph* G1, struct graph* G2, struct nodo** testa, int p){
	int i = 0;
	int gmax;
	struct edge* g1, *g2;
	
	//Ottiene la grandezza massima tra i due grafi per darla al grafo risultante
	if (G1->num_vertex < G2->num_vertex) {
        gmax = G2->num_vertex;
    } 
	else {
        gmax = G1->num_vertex;
    }
	
	//Crea il grafo per l'unione
	graph* G = createGraph(gmax);
	
	//Effettua l'unione tra i due grafi nel terzo se la somma dei pesi è quella data in input
	while(i < gmax){
		g1 = G1->adj[i];
        g2 = G2->adj[i];

        while (g1 != NULL) {
        	while(g2 != NULL){
        		
        		if(p == (g1->peso + g2->peso)){
        			addArco(G, i, g1->key, g1->peso);
				}
        			
        		g2 = g2->next;
			}
        	g1 = g1->next;
    	}
    	
		i++;
	}
	
	
	//Elimina un nodo della lista con valore p
	//Elimina il nodo se si trova in testa
	if((*testa)->elem == p) {
		struct nodo* succ = *testa;
		*testa = (*testa)->next;
		free(succ);
	}
	else{
		struct nodo* scorri = *testa;
			
		while(scorri && scorri->next) {
			if(scorri->next->elem == p) {
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


