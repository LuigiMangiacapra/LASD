/*
Scrivere una funzione che, dato un grafo orientato, calcoli tutti i gradi uscenti ed entranti di ciascun vertice.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct edge{
	int val;
	struct edge* next;
};

struct graph{
	struct edge** e;
	int n_val;
};


struct graph* inserimento_grafo(int n);
void stampa_grafo(struct graph* g);
void inserisci_arco(struct graph* g, int u, int v);
void gradi_entranti_e_uscenti(struct graph* g);


int main(){
	int n, u, v, n_v;
	char scelta;
	struct graph* gr = NULL;
	char *str;
	
	printf("Inserisci il numero di vertici da inserire nel grafo\n");
	scanf("%d", &n);
	
	gr = inserimento_grafo(n);
	printf("Vuoi inserire un vertice? y/n\n");
	scanf("%s", &scelta);
	
	while(scelta == 'y'){
		n_v++;
		printf("Inserire vertice di partenza\n");
		scanf("%d", &u);
		printf("Inserire vertice di arrivo\n");
		scanf("%d", &v);
		inserisci_arco(gr, u, v);
		
		if(n_v == gr->n_val){
			printf("limite raggiunto, impossibile inserire altri vertici\n");
			break;
		}
		
		printf("Vuoi inserire un altro vertice? y/n\n");
		scanf("%s", &scelta);
	}
	
	stampa_grafo(gr);
	
	gradi_entranti_e_uscenti(gr);
}


struct graph* inserimento_grafo(int n){
	int i = 0;
	struct graph* gr = (struct graph*) malloc(sizeof(struct graph*));
	if(gr == NULL){
		printf("Grafo non allocato correttamente\n");
	}
	else{
		gr->e = (struct edge**) malloc(n * sizeof(edge));
		if(gr->e == NULL){
			printf("Lista di adiacenza non allocata correttamente\n");
			free(gr);
			gr = NULL;
		}
		else{
			gr->n_val = n;
			while(i < n){
				gr->e[i] = NULL;
				i++;
			}
		}
	}
	return gr;
}


void inserisci_arco(struct graph* g, int u, int v){
	struct edge* adj;
	struct edge* ed = (edge*)malloc(sizeof(edge));
	if(ed == NULL){
		printf("Allocazione non effettuata correttamente\n");
	}
	else{
		//creazione nodo
		ed->val = v;
		ed->next = NULL;
		
		if(g->e[u] == NULL){
			g->e[u] = ed;
		}
		else{
			adj = g->e[u];
			
			while(adj->next != NULL){
				adj = adj->next;
			}
			adj->next = ed;
		}
	}
	
}


void stampa_grafo(struct graph* g){
	int i=0, ne=0;
	struct edge* ed;
	if(g != NULL){//stampa solo se il grafo non è vuoto
		printf("Il grafo possiede %d vertici\n\n", g->n_val);
		while(i < g->n_val){
			ed = g->e[i];
			printf("Nodi adiacenti al vertice %d", i);
			while(ed != NULL){
				printf("->%d", ed->val);
				ne++;
				ed = ed->next;
			}
			i++;
			printf("\n");
		}
		printf("il grafo ha %d archi\n", ne);
	}
}



void gradi_entranti_e_uscenti(struct graph* g){
	struct edge* e1, *e2;
	int ge = 0;
	int i, j; 
	int gu = 0;
	
	for(int i=0; i<g->n_val; i++){
		gu = 0;
		e1 = g->e[i];
		while(e1 != NULL){
			gu++;
			e1 = e1->next;
		}
		printf("il numero di gradi uscenti per il vertice %d e' %d\n", i, gu);
	}
	
	printf("\n");
	for(i=0; i<g->n_val; i++){
		
		ge = 0;
		for(j=0; j<g->n_val; j++){
		
			e2 = g->e[j];
			
			while(e2 != NULL){
				if(e2->val == i)
					ge++;
				e2 = e2->next;
			}
			
		}
		
		printf("il numero di gradi entranti per il vertice %d e' %d\n", i, ge);
	}
}


