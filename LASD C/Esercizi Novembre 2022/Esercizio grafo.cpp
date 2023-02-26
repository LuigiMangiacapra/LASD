/*
	Dato un grafo orientato pesato rappresentato con liste di adiacenza e un valore
	x, scrivere una funzione che modifichi il grafo in modo che ogni nodo abbia grado
	uscente almeno x.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct edge{
	int info;
	int peso;
	struct edge* next;
};

struct graph{
	int size;
	struct edge** adj;
};

struct graph* crea_grafo(int size);
void print_grafo(struct graph* grafo);
struct graph* inserisci_arco(struct graph* grafo, int u, int v);
void modify_outgoing_degrees(struct graph* grafo, int x);


int main(){
	int size, u, v, x;
	char ins;
	struct graph* grafo = NULL;
	printf("Inserire grandezza grafo\n");
	scanf("%d", &size);
	
	grafo = crea_grafo(size);
	printf("Vuoi inserire un arco?y/n\n");
	scanf("%s", &ins);
	
	while(ins == 'y'){
		
		printf("Inserire vertice sorgente\n");
		scanf("%d", &u);
		printf("Inserire vertice di arrivo\n");
		scanf("%d", &v);
		grafo = inserisci_arco(grafo, u, v);
		
		printf("Vuoi inserire un altro arco?y/n\n");
		scanf("%s", &ins);
		
	}
	
	print_grafo(grafo);
	printf("Digitare minimo grado uscente x\n");
	scanf("%d", &x);
	modify_outgoing_degrees(grafo, x);
	print_grafo(grafo);
}


struct graph* crea_grafo(int n){
	struct graph* grafo = (struct graph*)malloc(sizeof(struct graph));
	if(grafo == NULL){
		printf("Allocazione non riuscita\n");
	}
	else{
		grafo->adj = (struct edge**)malloc(n*sizeof(struct edge));
		if(grafo->adj == NULL){
			printf("Allocazione non riuscita\n");
			free(grafo);
			grafo = NULL;
		}
		else{
			grafo->size = n;
			for(int i=0; i<n; i++){
				grafo->adj[i] = NULL;
			}
		}
	}
	return grafo;
}


void print_grafo(struct graph* grafo){
	struct edge* e;
	int i = 0;
	int degree = 0;
	if(grafo != NULL){

		for(i = 0; i<grafo->size; i++){
			degree = 0;
			e = grafo->adj[i];
			printf("Il vertice %d ha i vertici:", i);
			while(e != NULL){
				printf("->%d", e->info);
				degree++;
				e = e->next;
			}
			printf(" il vertice %d ha grado uscente %d\n", i, degree);
			printf("\n");
		}
	}
}


struct graph* inserisci_arco(struct graph* grafo, int u, int v){
	struct edge* e, *ed;
	
	while(u >= grafo->size){
		printf("Il vertice di partenza non è presente nel grafo\n");
		printf("Reinserire nodo di arrivo\n");
		scanf("%d", &u);
	}
	
	e = grafo->adj[u];
	while(e != NULL){
		while(e->info == v){
			printf("Vertice di arrivo già presente\n");
			printf("Reinserire nodo di arrivo\n");
			scanf("%d", &v);
		}
		e = e->next;
	}
	
	struct edge* nuovo = (struct edge*)malloc(sizeof(struct edge));
	if(nuovo == NULL){
		printf("Allocazione non effettuata correttamente\n");
		exit(1);
	}
	else{
		nuovo->info = v;
		nuovo->next = NULL;
		
		if(grafo->adj[u] == NULL){
			grafo->adj[u] = nuovo;
		} 
		else{

			ed = grafo->adj[u];
			while(ed->next != NULL){
				ed = ed->next;
			}
			
			ed->next = nuovo;
		}
	}
	return grafo;
}


void modify_outgoing_degrees(struct graph* grafo, int x) {
    struct edge* e;
    int u, v;
    int i, degree, num_loops;
    //scorre i vertici
    for(i = 0; i < grafo->size; i++) {
        degree = 0;
        e = grafo->adj[i];
        //scorre le liste di adiacenza
        while(e != NULL) {
            degree++;//calcolo grado uscente
            e = e->next;
        }
        if(degree < x) {//Per ogni vertice controlla se il grado uscente è minore di x, se è minore di x allora aggiunge la differenza di elementi
        	
            num_loops = x - degree;
            
            //for per aggiungere altri 
            for(int j = 0; j < num_loops; j++) {
            	
				printf("Inserire vertice di arrivo\n");
				scanf("%d", &v);
				grafo = inserisci_arco(grafo, i, v);
            }
        }
    }
}


