/*
Si implementino in linguaggio C le seguenti operazioni utilizzando come struttura dati di appoggio un grafo, indipendentemente dal fatto che il grafo sia rappresentato con liste di adiacenza o con matrice di adiacenza:
Creazione della struttura dati grafo contenente tutte le città con le relative informazioni.
	- Aggiunta di un collegamento. V
	- Rimozione/modifica-lunghezza di un collegamento. V
	- Aggiunta di una città V
	- Cancellazione/modifica-dati di una città V
	- Stampa di tutte le città e delle relative informazioni V
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 20
#define MAX_NAME 256


//nodo della lista di adiacenza
typedef struct edge{
	char name[MAX_NAME];
	int distanza;//per creare un grafo pesato
	struct edge *next;//semplice next al prossimo elemento della lista
}edge;


//nodo rappresentante un vertice
typedef struct graph{
	edge* head;//testa della lista di adiacenza
	char name[MAX_NAME];//nome di ogni vertice
	struct graph* next;//successivo di ogni nodo della lista di adiacenza
}graph;


//Macro
int is_empty(graph *G) { return (G==NULL); }


//Prototipi
graph *crea_grafo(int n);
void g_add(graph *G, char* cit1, char* citta, int lung);
void g_print(graph *G);
graph* remove_coll(graph *G, char* u, char* v);
void Modifica_peso(graph *G, int n_peso, char* u, char* v);
graph* remove_city(graph* G, char* u);
void freeList(edge* L);


int main(){
	graph *G;
	int scelta, n_peso, gu, ge, peso_max,n, massimo, lung;
	char nome[MAX_NAME], cit[MAX_NAME];
	char u[MAX_NAME], v[MAX_NAME];
	do{
		printf("\nScegli l'operazione da svolgere\n");
		printf("1-Crea grafo, 2-Aggiungi_collegamento, 3-Mondifica_lunghezza_collegamento, 4-Rimuovi_collegamento, 5-Rimuovi_citta', 6-Stampa_grafo, 7-exit\n");
		scanf("%d",&scelta);
		switch(scelta){
			case 1:
				printf("Quanti vertici vuoi inserire?\n");
				scanf("%d", &n);
				if(n<MAX){
					G=crea_grafo(n);
					printf("Grafo vuoto creato\n");
				}
				else
					printf("20 è il numero massimo di elementi da poter inserire\n");
				
				break;
			case 2:
				printf("Aggiungi arco specificando vertice sorgente, vertice di arrivo e lunghezza:\n");
				printf("Specifica vertice sorgente:\n");
				scanf("%s", &cit);
				printf("Specifica vertice di arrivo(citta')\n");
				scanf("%s", &nome);
				printf("Specifica lunghezza collegamento\n");
				scanf("%d", &lung);
				g_add(G, cit, nome, lung);
				g_print(G);
				 
				break;
			case 3:
				printf("Modifica il peso di un arco specificando peso,vertice sorgente e di arrivo\n");
				printf("Specifica vertice sorgente:\n");
				scanf("%s", u);
				printf("Specifica vertice di arrivo:\n");
				scanf("%s", v);
				printf("Specifica nuovo peso\n");
				scanf("%d",&n_peso);
				
				Modifica_peso(G, n_peso, u, v);
			
				break;
			case 4:
				printf("Elimina arco specificando vertice sorgente e di arrivo:\n");
				printf("Specifica vertice sorgente:\n");
				scanf("%s",u);
				printf("Specifica vertice di arrivo:\n");
				scanf("%s",v);
				
				G=remove_coll(G, u, v);
				printf("Collegamento eliminato con successo\n");
				g_print(G);
				
				break;
			case 5:
				printf("Elimina arco specificando vertice sorgente e di arrivo:\n");
				printf("Specifica citta' da eliminare:\n");
				scanf("%s",u);
				
				G=remove_city(G, u);
				g_print(G);
				break;
			case 6:
				g_print(G);
		
		}
	
	}
	while(scelta==1 || scelta==2 || scelta==3 || scelta==4 || scelta==5 || scelta==6 || scelta==7 || scelta==8);
	
}



graph *crea_grafo(int n){
	graph *G;
	graph *g;
	int i;
	
	//Dà memoria al grafo
	G = (graph*)malloc(sizeof(graph));
	if(G==NULL)
		printf("ERRORE: impossibile allocare memoria per il grafo\n");
	else{
		//Dà memoria alla testa della lista
		G->head = (edge*)malloc(sizeof(edge));
		if(G->head==NULL){
			printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
			free(G);//Se non è possibile allocare memoria per la lista, il grafo non ha senso di esistere
			G=NULL;//G=NULL dopo aver liberato memoria in modo tale che l'indirizzo del grafo punti su una locazione nulla
					//e non vuota
		}
		else{
			printf("Inserire primo elemento\n");
			scanf("%s", G->name);
			G->head = NULL; //imposta la testa della lista di adiacenza in testa a NULL
			g = G;
			
			for(i=2;i<=n;i++){
				g->next=(graph *)malloc(sizeof(graph)); //alloca memoria per la creazione di un vertice della lista dei vertici
				g = g->next;
				
				g->head = (edge*)malloc(sizeof(edge)); //alloca memoria per la creazione di un nodo della lista di adiacenza
				g->head = NULL; //imposta a NULL ogni nodo della lista di adiacenza
				
				printf("inserire il %d elemento:\n",i);
				scanf("%s", g->name);
		 	}
			g->next=NULL;
		
		}
	}	
	return G;
}


void g_add(graph *G, char* cit1, char* citta, int lung){
	
	edge *new_edge, *e;
	graph* g, *g1;
	new_edge = (edge*)malloc(sizeof(edge));
	int flag = 0;
	
	if(new_edge==NULL){
		printf("ERRORE: impossibile allocare memoria \n");
	}
	else{
		//creazione nodo
		strcpy(new_edge->name, citta);
		new_edge->distanza = lung;
		new_edge->next = NULL;
		
		g1 = G;
		
		//Controlla se la città di partenza e di arrivo sono presenti nel grafo
		while(g1 != NULL){
			if((strcmp(g1->name, cit1) == 0) || (strcmp(g1->name, citta) == 0)){//controlla se le città sono presenti nella lista di vertici
				flag = 1;
			}
			if(flag == 0){
				printf("citta' di partenza o di arrivo non esistente\n");
				return;
			}
			g1 = g1->next;
		}
		
		
		g = G;
		//Scorre la lista di vertici
		while(g != NULL){				
			if(strcmp(g->name, cit1) == 0){

				//Se non ha elementi
				if(g->head==NULL){
					g->head = new_edge;
				}
				else{
					e = g->head;
					//scorre la lista di adiacenza fino all'elemento in coda
					while(e->next != NULL){
						e = e->next; 
					}
					//Aggiunge l'elemento in coda
					e->next = new_edge;
				}
				
			}
			g = g->next;
		}
	}
}


//Stampa grafo
void g_print(graph *G){
	int i;
	int ne=0;//conserva il numero di archi
	edge* e;//salva la lista da dover navigare
	graph* g = G;
	if(!is_empty(G)){
		
		//Scorre i vertici
		while(g != NULL){
			printf("nodi adiacenti al nodo %s",g->name);
			e = g->head;
			//scorre le liste di adiacenza
			while(e != NULL){
				printf("->%s",e->name);
				ne++;
				e = e->next;
			}
			printf("\n");
			g = g->next;
		}
		printf("il grafo ha %d archi\n", ne);
	}
}


graph* remove_coll(graph *G, char* u, char* v){
	edge* e;
	edge* tmp;
	graph* g = G;
	while(g != NULL){ //scorre la lista dei vertici
		if(strcmp(g->name, u) == 0){
			e = g->head;
			while(e != NULL){ //scorre le liste di adiacenza
				if(strcmp(e->name, v) == 0){ //se l'elemento è stato trovato
					//Importante
					if(e == g->head){ //se l'elemento da eliminare è in testa
						tmp = g->head;
						g->head = e->next;
						free(tmp);
					}
					else{ //se l'elemento non è in testa
						tmp = e;
						e = e->next;
						free(tmp);
					}
				}
				else
					e = e->next;
			}
		
		}
		g = g->next;
	}
	return G;
}



void Modifica_peso(graph* G, int n_peso, char* u, char* v){
	
	edge* e;
	graph* g = G;
	while(g != NULL){
		if(strcmp(g->name, u) == 0){
			e = g->head;
			while(e != NULL){
				if(strcmp(e->name, v) == 0){
					printf("La distanza %d tra %s e %s e' adesso", e->distanza, u, v);
					e->distanza = n_peso;
					printf(" %d\n", e->distanza);
					e = e->next;
				}
			}
		
		}
		g = g->next;
	}
}


graph* remove_city(graph* G, char* u){
	graph* g = G;
	graph* tmp1;
	edge* e;
	edge* tmp;
	while(g != NULL){
		//Elimina il vertice e la sua lista di adiacenza
		if(strcmp(g->name, u) == 0){
			if(g->head != NULL) //se il nodo attuale ha una lista di adiacenza con almeno un elemento
				freeList(g->head); //elimina la lista di adiacenza e ne libera la memoria
			if(G == g){//Importante (se il vertice da eliminare si trova in testa alla lista di vertici)
				tmp1 = G;
				G = g->next;//cambia la testa della lista
				g = g->next;
				free(tmp1);
			}
			else{
				tmp1 = g;
				g = g->next;
				free(tmp1);
			}
		}
		else{//Elimina il vertice da tutte le liste di adiacenza
			e = g->head;
			while(e != NULL){
				if(strcmp(e->name, u) == 0){
					if(e == g->head){//Importante
						tmp = g->head;
						g->head = e->next;
						e = e->next;
						free(tmp);
					}
					else{
						tmp = e;
						e = e->next;
						free(tmp);
					}
				}
				else
					e = e->next;
			}
			g = g->next;
		}
		
	}
	return G;
}


void freeList(edge* L) {
    if (L != NULL) {
        freeList(L->next);
        free(L);
        
    }
}
