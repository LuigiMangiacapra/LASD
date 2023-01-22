/*Si consideri un grafo G con V vertici ed E archi. Si implementino in
linguaggio C le seguenti operazioni utilizzando sia una rappresentazione con liste di adiacenza che con matrice di adiacenza:
Creazione di una struttura dati grafo pesata contenente tutti i vertici del
grafo G.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20 
typedef struct edge{
	int key;//chiave che rappresentano i vertici adiacenti nella posizione i-esima dell'array nel modello a liste di adiacenza
	int peso;//per creare un grafo pesato
	struct edge *next;//semplice next al prossimo elemento della lista
}edge;


typedef struct graph{
	int num_v;
	edge** adj;//contiene l'indirizzo dell'i-esima posizione dell'array che possiede l'indirizzo della lista
}graph;



int is_empty(graph *G) { return (G==NULL); }



//PROTOTIPI
graph* crea_grafo(int n);
void Modifica_peso(graph *G, int n_peso,int u, int v);
void g_print(graph *G);
void g_add(graph *G, int u, int v);
graph* remove(graph *G, int u, int v);
int grado_uscente(graph *G, int u);
int grado_entrante(graph *G, int v);
int arco_peso_max(graph *G);
void g_print(graph *G);
graph *unisci_vertici(graph *G1, graph *G2);
graph *unisci_archi(graph *G1, graph *G2, graph *G3);
graph *interseca_vertici(graph *G1, graph *G2);
graph *interseca_archi(graph *G1, graph *G2, graph *G4);
graph *differenza_vertici(graph *G1, graph *G2);
graph *differenza_archi(graph *G1, graph *G2, graph *G5);


int main(){
	
	int scelta, u, v, n_peso, gu, ge, peso_max, n, n2, massimo;
	int arco, arco2;
	graph *G1, *G2;
	
	//Primo grafo	
	printf("Primo grafo\n");
	printf("Quanti vertici vuoi inserire?\n");
	scanf("%d", &n);
	while(n>MAX){
		printf("Massimo %d elementi...", MAX);
		scanf("%d", &n);
	}
	G1=crea_grafo(n);
	printf("Grafo vuoto creato\n");
	
	printf("Vuoi inserire un arco? 1 o 2\n");
	scanf("%d", &arco);
	
	while(arco==1){
		printf("Aggiungi arco specificando vertice sorgente e di arrivo:\n");
		printf("Specifica vertice sorgente:\n");
		scanf("%d",&u);
		printf("Specifica vertice di arrivo\n");
		scanf("%d",&v);
		g_add(G1, u, v);
		g_print(G1);
		
		printf("Vuoi inserire un arco? 1 o 2\n");
		scanf("%d", &arco);
	}
	
	//Secondo grafo
	printf("\n\nSecondo grafo\n");
	printf("Quanti vertici vuoi inserire?\n");
	scanf("%d", &n2);
	while(n2>MAX){
		printf("Massimo %d elementi...", MAX);
		scanf("%d", &n2);
	}
	G2=crea_grafo(n2);
	printf("Grafo vuoto creato\n");
	
	printf("Vuoi inserire un arco? 1 o 2\n");
	scanf("%d", &arco2);
	
	while(arco2==1){
		printf("Aggiungi arco specificando vertice sorgente e di arrivo:\n");
		printf("Specifica vertice sorgente:\n");
		scanf("%d",&u);
		printf("Specifica vertice di arrivo\n");
		scanf("%d",&v);
		g_add(G2, u, v);
		g_print(G2);
		
		printf("Vuoi inserire un arco? 1 o 2\n");
		scanf("%d", &arco2);
	}
	
	printf("\n\nUnione tra vertici\n");
	graph *G3;
	G3 = unisci_vertici(G1, G2);
	unisci_archi(G1, G2, G3);
	g_print(G3);
	
	printf("\n\nIntersezione tra vertici");
	graph *G4;
	G4 = interseca_vertici(G1, G2);
	interseca_archi(G1, G2, G4);
	g_print(G4);
	
	printf("\n\nDifferenza tra vertici");
	graph *G5;
	G5 = differenza_vertici(G1, G2);
	if(G5!=NULL)//i grafi potrebbero avere lo stesso numero di vertici
		differenza_archi(G1, G2, G5);
	g_print(G5);
	
}



//creazione grafo vuoto (senza le varie liste di adiacenza)
graph* crea_grafo(int n){//prende in input il numero di vertici per assegnarli successivamente alla struttura
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
			G->num_v=n;//assegna a G->num il numero di vertici dato in input
			for(i=0; i<n; i++)
				G->adj[i]=NULL;
			}
			
		}
	return G;
}




//Modifica peso
void Modifica_peso(graph *G, int n_peso,int u, int v){
	edge *e;
	e=G->adj[u];
	while(e!=NULL){
		if(e->key==v){
			e->peso==n_peso;
		}
		e=e->next;
	}

}


//Stampa grafo
void g_print(graph *G){
	int i;
	int ne=0;//conserva il numero di archi
	edge* e;//salva la lista da dover navigare
	if(!is_empty(G)){
		printf("\nil grafo ha %d vertici\n",G->num_v);
		for(i=0;i<G->num_v;i++){
			printf("nodi adiacenti al nodo %d",i);
			e=G->adj[i];//"e" punta alla lista in posizione i
			//scorre la lista
			while(e!=NULL){
				printf("->%d",e->key);
				ne++;
				e=e->next;
			}
			printf("\n");
		}
		printf("il grafo ha %d archi\n", ne);
	}
}



//Aggiunge arco
void g_add(graph *G, int u, int v){//u è il nodo da cui esce l'arco, v è il nodo in cui entra
	edge *new1, *e; 
	int i = 0;
	int flag = 0;
	
	//frammento di codice per controlli vari sull'array
	
	while(i < G->num_v){
		if(u==i){
			flag = 1;
		}
		
		i++;
	}
	//Se non trova elementi compatibili ad u, non può essere inserito l'arco
	if(flag == 0){
		printf("l'arco uscente dal vertice %d non puo' essere inserito", u);
		return;
	}

	new1 = (edge*)malloc(sizeof(edge));
	if (new1==NULL) printf("ERRORE: impossibile allocare memoria \n");
	else {
		new1->key=v; 
		new1->next=NULL;
		if (G->adj[u] == NULL){//u non ha archi //
			G->adj[u] = new1;
		}	
		else {
			e=G->adj[u];
			if(v==e->key){
				printf("il vertice %d non puo' essere inserito perche' gia' presente\n", v);
				return;
			}
			
			//scorre la lista di adiacenza fino alla coda
			while(e->next!=NULL){ 
				if(v==e->key){
					printf("il vertice %d non puo' essere inserito perche' gia' presente\n", v);
					return;
				}
				e=e->next; 
			}
			if(v==e->key){
				printf("il vertice %d non puo' essere inserito perche' gia' presente\n", v);
				return;
			}
			//Aggiunge l'elemento in coda
			e->next=new1;
		} 	
			
	} 
}



//Cancellazione arco
graph* remove(graph *G, int u, int v){
	edge *tmp;//è un puntatore quindi ha bisogno dell'asterisco
	edge *e;
	if(G->adj[u]!=NULL){
		e=G->adj[u];
		if(e->key==v){
			tmp=e;
			e=e->next;
			free(tmp);
		}
		else{
			G=remove(G, u, e->next->key);//il valore ritornato è un grafo quindi ritorna in G, e->next ritorna un valore edge, e->next->key un valore int
			
		}
	}
	return G;
}


//Calcolo grado uscente e entrante di un nodo (Grafo orientato)
int grado_uscente(graph *G, int u){
	edge *e;
	int gradousc=0;
	e=G->adj[u];
	while(e!=NULL){
		gradousc++;
	}
	return gradousc;
}

int grado_entrante(graph *G, int v){
	edge *e;
	int gradoent=0;
	for(int i=0; i<G->num_v; i++){
		e=G->adj[i];
		while(e!=NULL){
			if(e->key==v){
				gradoent++;
			}
		}
	}
	return gradoent;

}

//Calcolo dell arco con peso maggiore 
int arco_peso_max(graph *G){
	edge *e;
	int pesomax=0;
	for(int i=0; i<G->num_v; i++){
		e=G->adj[i];
		while(e!=NULL){
			if(pesomax<e->peso){
				pesomax=e->peso;
			}
			e=e->next;
		}
	}
	return pesomax;
}


graph* unisci_vertici(graph *G1, graph *G2){
	graph *G;
	int i,n,j;
	G=(graph*)malloc(sizeof(graph));//alloca memoria per il nuovo grafo
	if(G==NULL)
		printf("ERRORE: impossibile allocare memoria per il grafo\n");
	else{
		if(G1->num_v > G2->num_v){
			n = G1->num_v;
		}
		else
			n = G2->num_v;
			
		G->adj = (edge**)malloc(n*sizeof(edge*));//alloca memoria per la lista di adiacenza collegandolo al campo adj della struct del grafo
		if (G->adj==NULL) {
			printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
			free(G);//Se non è possibile allocare memoria per la lista, il grafo non ha senso di esistere
			G=NULL;//G=NULL dopo aver liberato memoria in modo tale che l'indirizzo del grafo punti su una locazione nulla
					//e non vuota
		}
		else{
			//effettua l'unione dei vertici, poiché l'unica cosa che può cambiare tra un grafo e l'altro è la quantità di vertici, si punta a quella
			while (i < n){
				G->adj[i]=NULL;
				i++;
			}
			G->num_v = n;
			
			
		}	
	}
	return G;

}

graph *unisci_archi(graph *G1, graph *G2, graph *G3){
	edge *g1, *g2;
	int i = 0, j = 0;
	
	
	//Scorre l'array contenente i vertici del grafo G1
	while(i < G1->num_v){
		g1 = G1->adj[i];
		
		if(g1 != NULL){//scorre solo se il singolo vertice possiede archi
			//Scorre la lista di adiacenta per i vertici i in G1 
			while(g1 != NULL){
				g_add(G3, i, g1->key);//poiché g_add possiede già i controlli per non inserire ripetizioni, non c'è bisogno di aggiugnere ulteriori ripetizioni
				g1 = g1->next;
			}
			
		}
		i++;
	}
	
	
	//Scorre l'array contenente i vertici del grafo G2
	while(j < G2->num_v){
		g2 = G2->adj[j];
	
		if(g2 != NULL){
			//Scorre la lista di adiacenta per i vertici j in G2
			while(g2 != NULL){
				g_add(G3, j, g2->key);//poiché g_add possiede già i controlli per non inserire ripetizioni, non c'è bisogno di aggiugnere ulteriori ripetizioni
				g2 = g2->next;
			}
		}
		j++;
	}
	
	return G3;
}



graph* interseca_vertici(graph *G1, graph *G2){
	graph *G;
	int i,n,j;
	G=(graph*)malloc(sizeof(graph));//alloca memoria per il grafo
	if(G==NULL)
		printf("ERRORE: impossibile allocare memoria per il grafo\n");
	else{
		//si prende il numero di vertici inferiore ai due grafi
		if(G1->num_v < G2->num_v){
			n = G1->num_v;
		}
		else
			n = G2->num_v;
			
		G->adj = (edge**)malloc(n*sizeof(edge*));//alloca memoria per la lista di adiacenza collegandolo al campo adj della struct del grafo
		if (G->adj==NULL) {
			printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
			free(G);//Se non è possibile allocare memoria per la lista, il grafo non ha senso di esistere
			G=NULL;//G=NULL dopo aver liberato memoria in modo tale che l'indirizzo del grafo punti su una locazione nulla
					//e non vuota
		}
		else{
			//effettua l'unione dei vertici, poiché l'unica cosa che può cambiare tra un grafo e l'altro è la quantità di vertici, si punta a quella
				
			while (i < n){
				G->adj[i]=NULL;
				i++;
			}
			G->num_v = n;
			
		}	
	}
	return G;

}


graph *interseca_archi(graph *G1, graph *G2, graph *G4){
	
	edge *g1, *g2;
	int gmin;
	int i = 0, j = 0;
	
	if(G1->num_v > G2->num_v){
		gmin=G2->num_v;
	}
	else{
		gmin=G1->num_v;
	}
	
	//Scorre l'array contenente i vertici del grafo G1 e G2
	while(i < gmin){
		g1 = G1->adj[i];
			
		//Scorre la lista di adiacenta per i vertici i in G1 
		while(g1 != NULL){
			g2 = G2->adj[i];
			while(g2 != NULL){
				if(g1->key == g2->key){
					g_add(G4, i, g1->key);
				}
				g2 = g2->next;
			}
			g1 = g1->next;
		}
		i++;
	}
	
	return G4;
	
}


graph* differenza_vertici(graph *G1, graph *G2){
	graph *G;
	int i,n,j;
	
	//CREAZIONE GRAFO
	G=(graph*)malloc(sizeof(graph));//alloca memoria per il grafo
	if(G==NULL)
		printf("ERRORE: impossibile allocare memoria per il grafo\n");
	else{
		
		if(G1->num_v > G2->num_v){
			n = G1->num_v - G2->num_v;
		}
		else
			n = G2->num_v - G1->num_v;
			
		G->adj = (edge**)malloc(n*sizeof(edge*));//alloca memoria per la lista di adiacenza collegandolo al campo adj della struct del grafo
		if (G->adj==NULL) {
			printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
			free(G);//Se non è possibile allocare memoria per la lista, il grafo non ha senso di esistere
			G=NULL;//G=NULL dopo aver liberato memoria in modo tale che l'indirizzo del grafo punti su una locazione nulla
					//e non vuota
		}
		else{
			//effettua l'unione dei vertici, poiché l'unica cosa che può cambiare tra un grafo e l'altro è la quantità di vertici, si punta a quella
			
			while (i < n){
				G->adj[i]=NULL;
				i++;
			}
			G->num_v = n; 
		
		}	
	}
	return G;

}



graph *differenza_archi(graph *G1, graph *G2, graph *G5){
	
	edge *g1, *g2;
	int gmin;
	int i = 0, j = 0;
	int flag = 0;
	if(G1->num_v<G2->num_v){
		gmin=G2->num_v;
	}
	else{
		gmin=G1->num_v;
	}
	
	//Scorre l'array contenente i vertici del grafo G1 e G2
	while(i < gmin){
		g1 = G1->adj[i];
			
		//Scorre la lista di adiacenta per i vertici i in G1 
		while(g1 != NULL){
			g2 = G2->adj[i];
			flag = 0;
			while(g2 != NULL){
				if(g1->key == g2->key){
					flag = 1;
				}
				
				g2 = g2->next;
			}
			if(flag == 0){
				g_add(G5, i, g1->key);
			}
			g1 = g1->next;
		}
		
		
		g2 = G2->adj[i];
		while(g2 != NULL){
			g1 = G1->adj[i];
			flag = 0;
			while(g1 != NULL){
				if(g1->key == g2->key){
					flag = 1;
				}
				
				g1 = g1->next;
			}
			if(flag == 0){
				g_add(G5, i, g2->key);
			}
			g2 = g2->next;
		}
		i++;
	}

	
	return G5;
	
}

