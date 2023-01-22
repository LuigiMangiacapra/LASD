/*Si consideri un grafo G con V vertici ed E archi. Si implementino in
linguaggio C le seguenti operazioni utilizzando sia una rappresentazione con liste di adiacenza che con matrice di adiacenza:
Creazione di una struttura dati grafo pesata contenente tutti i vertici del
grafo G.
Modifica di un peso.
Aggiunta di un arco.
Cancellazione di un arco
Calcolo del grado uscente e entrante di un nodo.
Calcolo dell arco con peso maggiore 
Scrivere in linguaggio C un programma che implementi le
operazioni precedenti indipendentemente dal fatto che la struttura 
dati di appoggio sia un grafo rappresentato con liste di adiacenza o 
con matrice di adiacenza.
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

int empty_queue(int Q[])
{
return Q[0]==0;
}


//PROTOTIPI
graph* crea_grafo(int n);
void g_print(graph *G);
void g_add(graph *G, int u, int v);
void dfs(struct graph *g);
void dfs1(struct graph *g, int i, int *aux);
graph *grafo_trasposto(graph *G);
void push(int S[], int val, int *err);


int main(){
	int u, v, n;
	char arco;
	graph *G1, *G2;
	
	printf("Quanti vertici vuoi inserire?\n");
	scanf("%d", &n);
	while(n>MAX){
		printf("Massimo %d elementi...", MAX);
		scanf("%d", &n);
	}
	G1=crea_grafo(n);
	printf("Grafo vuoto creato\n");
	
	printf("Vuoi inserire un arco? y/n\n");
	scanf("%s", &arco);
	
	if(arco == 'n'){
		return 0;		
	}
	
	while(arco != 'y' || arco != 'n')
		printf("Risposta non valida!\nInserire y o n\n");
		
	while(arco=='y'){
		printf("Aggiungi arco specificando vertice sorgente e di arrivo:\n");
		printf("Specifica vertice sorgente:\n");
		scanf("%d",&u);
		printf("Specifica vertice di arrivo\n");
		scanf("%d",&v);
		g_add(G1, u, v);
		g_print(G1);
		
		printf("Vuoi inserire un arco? y/n\n");
		scanf("%d", &arco);
		
		if(arco == 'y' || arco == 'n'){
			if(arco == 'n'){
				return 0;		
			}
		}
		else
			printf("Risposta non valida!\nInserire y o n\n");
	}
	
	dfs(G1);
	
	G2 = grafo_trasposto(graph *G);
	
	dfs(G2);
	
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
	//Aggiungere frammento di codice per controlli vari
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
			//scorre la lista di adiacenza fino alla coda
			while(e->next!=NULL){
				e=e->next; 
			}
			//Aggiunge l'elemento in coda
			e->next=new1;
		} 	
			
	} 
}



//Visita in profondità
void dfs(graph *g) {
	int i;
	//Alloca un array di appoggio per memorizzare quando un vertice è stato incontrato
	int *aux = (int*)calloc(g->num_v, sizeof(int)); 
	int *f = (int*)calloc(g->num_v, sizeof(int)); 
	
	if(!aux) {
		printf("Errore di Allocazione\n");
	}
	else { 
		for(i = 0; i < g->num_v; i++){//Scorre i vertici del grafo
			if(!aux[i]) {//Se il vertice non è stato ancora incontrato
				printf("\n%d,",i); 
				dfs1(g,i,aux, f);//Chiama la funzione ricorsiva dfs1 su ogni vertice
			}
		}
		free(aux);//Dopo aver utilizzato l'array viene liberata la memoria dedicatagli
	}
}


void dfs1(graph *g, int i, int *aux, int *f) {
	edge *e; 
	aux[i] = 1;//aux[i] impostato ad uno perché il vertice corrente è stato appena visitato
	e = g->adj[i];
	int err = 0;
	
	while(e != NULL){//Scorre i vertici adiacenti ad i
		e = e->next;
		if(!aux[e->key]) {//Se il vertice successivo è stato visitato (!= 0)
			printf("%d,",e->key); 
			dfs1(g,e->key,aux);//Chiamata ricorsiva sul vertice adiacente dell'adiacente
		}
		
	push(f[], i, err);
	}
}


/*RIASSUNTO VISITA IN PROFONDITA'
	La visita in profondita parte da un vertice i e agisce ricorsivamente per visitare il vertice
	adiacente, l'adiacente dell'adiacente e così via fino ad arrivare al vertice che non ha 
	vertici adiacenti cioè il vertice di arrivo.
	Una volta raggiunto questo vertice si effettua la risalita e per ogni vertice visitato
	nella risalita si controllano i suoi adiacenti non visitati (aux[i]=1) (ammesso che li abbia)

*/

graph *grafo_trasposto(graph *G){
	graph* G2 = crea_grafo(G->num_v);//Crea il grafo trasposto
	edge *e;
	
	//Scorre i vertici
	while(i < G2->num_v){
		e = G2->adj[i];
		while(e != NULL){
			g_add(G2, e->key, i);
		}
	}
	return G2;
}

void push(int S[], int val, int *err)
{
	if (full_stack(S)) 
		*err=1;
	else 
	{
		S[0] = S[0]+ 1;
		S[S[0]]= val;
		*err=0;
	}
}	


