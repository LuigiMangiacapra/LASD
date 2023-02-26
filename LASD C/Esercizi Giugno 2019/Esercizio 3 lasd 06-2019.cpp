/*
Scrivere in linguaggio C una funzione che preso in input il grafo G e il grafo
H, restituisca il grafo T tale che ogni arco in T è presente sia in G che in H
e che il peso di ogni arco p sia la somma dei pesi degli archi di G ed H e che
sia pari e maggiore di 10

1)Confrontare i grafi G e H
2)Ricavare dal confronto gli archi in comune dei due grafi
3)inserire gli archi nel grafo se la somma dei pesi è maggiore di 10

*/
#include <stdio.h>
#include <malloc.h>
#define MAX 20

typedef struct edge{
	int key;
	edge* next;
	int peso;
}edge;


typedef struct graph{
	int nv;
	edge **adj;
}graph;


int is_empty(graph *G) { return (G==NULL); }


graph* crea_grafo(int n);//prende in input il numero di vertici da inserire
void Modifica_peso(graph *G, int n_peso,int u, int v);
void g_print(graph *G);
void g_add_arco(graph *G, int u, int v);
void confronta_grafi(graph *G1, graph *G2);


int main(){
	int n_graph,n,i,l=1;
	printf("Quante liste vuoi creare?\n");
	scanf("%d",&n_graph);
	
	while(n_graph){
		graph* g;
		int u, v;
		printf("Inserire vertici nel %d° grafo\n", l); 
		printf("Quanti elementi vuoi inserire?\n");
		scanf("%d",&n);
		if(n<MAX){
			g=crea_grafo(n);
			printf("Grafo vuoto creato\n");
		}
		else
			printf("Troppi elementi! Riinserire\n");
		
		do{
			printf("Cosa vuoi fare?\n");
			printf("Se vuoi inserire un arco digita 1, 2 per stampare, 3 per uscire\n");
			scanf("%d",&i);
			switch(i){
				case 1:
					printf("Inserire archi:\n");
					printf("Indicare vertice di partenza:\n");
					scanf("%d",&u);
					printf("Indicare vertice di arrivo:\n");
					scanf("%d",&v);
					g_add_arco(g,u,v); 
				break;
				case 2:
					g_print(g);
			}
		}
		while(i==1 || i==2);
		
		l++;
		n_graph--;
		
	}
}

graph* crea_grafo(int n){
	graph* G;
	G=(graph*)malloc(sizeof(graph*));
	if(G==NULL){
		printf("Impossibile allocare memoria\n");
	}
	else{
		G->adj=(edge**)malloc(n*sizeof(edge*));//Allocazione array di n vertici
		if(G->adj==NULL){
			printf("Impossibile allocare memoria\n");
			free(G);
			G=NULL;
		}
		else{
			for(int i=0; i<n;i++){
				G->adj[i]=NULL;
			}
		} 
	}
	return G;

}


void g_print(graph* G){
	int na;
	edge *e;
	 if(!is_empty(G)){
	 	printf("Il grafo ha %d vertici\n",G->nv);
	 	for(int i=0; i<G->nv; i++){//shifta l'array di vertici
		 	printf("Numero di vertici adiacenti al vertice %d\n", i);
		 	e=G->adj[i];
		 	while(e!=NULL){
				printf("%d",e->key);			
				na++; 
				e=e->next;
			}
		}
		printf("Il numero di archi è: %d\n",na);
	 
	 }

}


void g_add_arco(graph *G, int u, int v){
	edge *new1, *e; 
	new1 = (edge*)malloc(sizeof(edge));//allocazione memoria
	if (new1==NULL) printf("ERRORE: impossibile allocare memoria \n");
	else {
		//preparazione vertice di arrivo dell'arco a inserire
		new1->key=v; 
		new1->next=NULL;
		if (G->adj[u] == NULL) //se u non ha archi, inserisce il primo elemento della lista
			G->adj[u] = new1;
		else {
			e=G->adj[u];
			while(e->next!=NULL)
				e=e->next; 
			} 
			e->next=new1;
	}
}


void confronta_grafi(graph *G, graph *H){
	int i, j;
	graph *T;
	while(i<G->nv && j<H->nv){
		if(G->adj[i]==H->adj[j]){
			e=G->adj[i];
			f=H->adj[j];
			while(e!=NULL){
				while(f!=NULL){
					if(e->key==f->key && (e->peso)+(f->peso)>10){
						g_add_Arco(T, i, e->key);
						
					}
				}
			
			}
		}
	}


}
