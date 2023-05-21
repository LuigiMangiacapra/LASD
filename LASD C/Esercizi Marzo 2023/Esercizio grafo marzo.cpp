/*
Creare due grafi pesati ed effettuare la loro differenza tra i vertici che hanno un peso inferiore a quello dato in input.
*/

#include <stdio.h>
#include <stdlib.h>

struct edge{
	int info;
	int peso;
	struct edge* next;
};

struct graph{
	int num_v;
	struct edge** adj;
};

void g_add(struct graph* G, int u, int v, int peso);
struct graph* crea_grafo(int n_elem);
void g_add(graph *G, int u, int v, int peso);
void stampa_grafo(struct graph* G);
struct graph* differenza_grafi(struct graph* G1, struct graph* G2);


int main(){
	int n_elem;
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
	
	grafo3 = differenza_grafi(grafo1, grafo2);
	stampa_grafo(grafo3);

}

struct graph* crea_grafo(int n){
	struct graph *G;
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
			G->num_v=n;//assegna a G->num il numero di vertici dato in input
			for(i=0; i<n; i++)
				G->adj[i]=NULL;
		}
			
	}
	return G;
}


//Aggiunge arco
void g_add(struct graph* G, int u, int v, int peso){
	struct edge *new1, *e;
	new1 = (struct edge*)malloc(sizeof(struct edge));
	if (new1==NULL)
		printf("ERRORE: impossibile allocare memoria \n");
	else {
		new1->info = v;
		new1->peso = peso;
		new1->next = NULL;

		if (G->adj[u] == NULL){
			G->adj[u] = new1;
		}
		else {
			e=G->adj[u];
			while(e->next!=NULL){
				e=e->next;
			}
			e->next=new1;
		} 	
	} 
}

void stampa_grafo(struct graph* G){
	int i;
	int ne=0;//conserva il numero di archi
	struct edge* e;//salva la lista da dover navigare
	if(G != NULL){
		printf("\nil grafo ha %d vertici\n",G->num_v);
		for(i=0;i<G->num_v;i++){
			printf("nodi adiacenti al nodo %d",i);
			e=G->adj[i];//"e" punta alla lista in posizione i
			//scorre la lista di adiacenza
			while(e!=NULL){
				printf("->%d",e->info);
				ne++;
				e=e->next;
			}
			printf("\n");
		}
		printf("il grafo ha %d archi\n", ne);
	}
}



struct graph* differenza_grafi(struct graph* G1, struct graph* G2) {
    struct graph* G = NULL;
    struct edge *g1, *g2;
    int gmin;
    int i = 0;
    int flag = 0;

    if (G1->num_v < G2->num_v) {
        gmin = G2->num_v;
    } else {
        gmin = G1->num_v;
    }

    G = crea_grafo(gmin);

    while (i < G1->num_v && i < G2->num_v) {
        g1 = G1->adj[i];
        g2 = G2->adj[i];

        while (g1 != NULL) {
            flag = 0;
            struct edge* current = G2->adj[i];
            while (current != NULL) {
                if (g1->info == current->info) {
                    flag = 1;
                    break;
                }
                current = current->next;
            }
            if (flag == 0) {
                g_add(G, i, g1->info, g1->peso);
            }
            g1 = g1->next;
        }

        while (g2 != NULL) {
            flag = 0;
            struct edge* current = G1->adj[i];
            while (current != NULL) {
                if (current->info == g2->info) {
                    flag = 1;
                    break;
                }
                current = current->next;
            }
            if (flag == 0) {
                g_add(G, i, g2->info, g2->peso);
            }
            g2 = g2->next;
        }

        i++;
    }

    while (i < G1->num_v) {
        g1 = G1->adj[i];
        while (g1 != NULL) {
            g_add(G, i, g1->info, g1->peso);
            g1 = g1->next;
        }
        i++;
    }

    while (i < G2->num_v) {
        g2 = G2->adj[i];
        while (g2 != NULL) {
            g_add(G, i, g2->info, g2->peso);
            g2 = g2->next;
        }
        i++;
    }

    return G;
}


