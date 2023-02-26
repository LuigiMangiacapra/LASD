/*
	Creare due grafi ed effettuare la differenza tra i due se è possibile

*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

struct edge{
	int info;
	struct edge* next;
};

struct graph{
	int size;
	struct edge **adj;
};

struct graph* crea_grafo(int n);
void g_print(struct graph* g);
void g_add(struct graph* g, int u, int v);
struct graph* differenza(struct graph* g1, struct graph* g2);


int main(){
	int n_v;
	struct graph* g, *g1, *g2, *g3;
	int arc, u, v;
	printf("Inserire primo Grafo\n");
	printf("Inserire il numero di vertici\n");
	scanf("%d", &n_v);
	
	while(n_v > MAX){
		printf("Inserire max %d vertici\n", MAX);
		scanf("%d", &n_v);
	}

	g1 = crea_grafo(n_v);
	
	printf("Vuoi inserire un arco nel grafo? y/n\n");
	scanf("%d", &arc);
	
	while(arc == 1){
		
		printf("Inserire vertice di origine\n");
		scanf("%d", &u);
		printf("Inserire vertice di arrivo\n");
		scanf("%d", &v);
		
		g_add(g1, u, v);
		
		printf("Vuoi inserire un altro arco nel grafo? y/n\n");
		scanf("%d", &arc);
	}
	
	g_print(g1);
	
	
	
	printf("Inserire secondo Grafo\n");
	printf("Inserire il numero di vertici\n");
	scanf("%d", &n_v);
	
	while(n_v > MAX){
		printf("Inserire max %d vertici\n", MAX);
		scanf("%d", &n_v);
	}
	
	g2 = crea_grafo(n_v);
	
	printf("Vuoi inserire un arco nel grafo? y/n\n");
	scanf("%d", &arc);
	
	while(arc == 1){
		
		printf("Inserire vertice di origine\n");
		scanf("%d", &u);
		printf("Inserire vertice di arrivo\n");
		scanf("%d", &v);
		
		g_add(g2, u, v);
		
		printf("Vuoi inserire un altro arco nel grafo? y/n\n");
		scanf("%d", &arc);
	}
	
	g_print(g2);
	
	g3 = differenza(g1, g2);
	
	g_print(g3);
}


struct graph* crea_grafo(int n){
	int i = 0;
	struct graph* g = (struct graph*)malloc(sizeof(struct graph*));
	if(g == NULL){
		printf("L'allocazione non è stata effettuata correttamente\n");
	}
	else{
		g->adj = (struct edge**)malloc(sizeof(struct edge*) * n);
		if(g->adj == NULL){
			printf("L'allocazione non è stata effettuata correttamente\n");
			free(g);
			g = NULL;
		}
		else{
			g->size = n;
			for(i = 0; i < n; i++){
				g->adj[i] = NULL;
			
			}
		}
	}
	return g;	
}



void g_print(struct graph* g){
	struct edge* e;
	int ne = 0;
	if(g != NULL){
		printf("Il grafo possiene %d vertici\n", g->size);
		for(int i = 0; i < g->size; i++){
			
			e = g->adj[i];
			printf("Nodi adiacenti al vertice %d", i);
			
			while(e != NULL){
				printf("->%d",e->info);
				ne++;
				e = e->next;
			}
			printf("\n");
		}
		printf("il grafo ha %d archi\n", ne);
	}
}



void g_add(struct graph* g, int u, int v){
	
	struct edge* e;
	int flag = 0;
	
	if(u >= g->size){
		printf("Il vertice di partenza non e' presente nel grafo\n");
		return;
	}
	
	e = g->adj[u];
	while(e != NULL){
		if(e->info == v){
			printf("L'arco che si vuole inserire e' gia' presente\n");
			flag = 1;
			break;
		}
		e = e->next;
	}
	
	if(flag == 0){
		struct edge* new1 = (struct edge*)malloc(sizeof(struct edge*));
		
		if(new1 == NULL){
			printf("Allocazione non riuscita!\n");
		}
		else{
			new1->info = v;
			new1->next = NULL;
			
			if(g->adj[u] == NULL){
				g->adj[u] = new1;
			}
			else{
				e = g->adj[u];
				while(e->next != NULL){
					e = e->next;
				}
				e->next = new1;
			}
		}
	}
}



struct graph* differenza(struct graph* g1, struct graph* g2) {
    int s = 0;
    struct edge* e1, *e2;

    if (g1->size >= g2->size) {
        s = g1->size;
    } else {
        return NULL;
    }

    struct graph* g3 = crea_grafo(s);
	
	//Scorre i vertici del primo grafo
    for (int i = 0; i < g1->size; i++) {
        int present = 0; //variabile per tracciare i valori presenti 
		
		//Scorre i vertici del secondo grafo
        for (int j = 0; j < g2->size; j++) {
        	//se il singolo vertice presenti in entrambi i grafi hanno degli archi
            if (g1->adj[i] != NULL && g2->adj[j] != NULL && i == j) {
                present = 1;
                break;
            }
        }
		//Se un vertice non è presente in entrambi i grafi viene inserito nel grafo risultante
        if (!present) {
            g3->adj[i] = g1->adj[i];
        } 
		else {
            e1 = g1->adj[i];
            while (e1 != NULL) {
                e2 = g2->adj[i];
                int found = 0;

                while (e2 != NULL) {
                    if (e1->info == e2->info) {
                        found = 1;
                        break;
                    }
                    e2 = e2->next;
                }
				
				//Aggiunge tutti i vertici che non sono presenti in entrambi i grafi
                if (!found) {
                    g_add(g3, i, e1->info);
                }

                e1 = e1->next;
            }
        }
    }

    return g3;
}

