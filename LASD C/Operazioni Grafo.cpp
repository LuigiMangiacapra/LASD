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
void Modifica_peso(graph *G, int n_peso,int u, int v);
void g_print(graph *G);
void g_add(graph *G, int u, int v);
graph* remove(graph *G, int u, int v);
int grado_uscente(graph *G, int u);
int grado_entrante(graph *G, int v);
int arco_peso_max(graph *G);
void g_print(graph *G);
void dfs(struct graph *g);
void dfs1(struct graph *g, int i, int *aux);
void bfs(struct graph *g);
void bfs1(struct graph *g, int i, int *aux);
void enqueue(int Q[], int valore);
int dequeue(int Q[]);
int arco_peso_min(graph *G);
void destroyqueue(int Q[]);

int main(){
	graph *G;
	int scelta, u, v, n_peso, gu, ge, peso_max,n, massimo;
	
	do{
		printf("\nScagli l'operazione da svolgere\n");
		printf("1-Crea grafo, 2-Aggiungi_arco, 3-Mondifica_un_peso, 4-Cancella_arco, 5-Grado_uscente, 6-Grado_entrante, 7-Arco_con_peso_maggiore, 8-Stampa_grafo, 9-exit\n");
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
				printf("Aggiungi arco specificando vertice sorgente e di arrivo:\n");
				printf("Specifica vertice sorgente:\n");
				scanf("%d",&u);
				printf("Specifica vertice di arrivo\n");
				scanf("%d",&v);
				g_add(G, u, v);
				
				break;
			case 3:
				printf("Modifica il peso di un arco specificando peso,vertice sorgente e di arrivo\n");
				printf("Specifica peso modificante\n");
				scanf("%d",&n_peso);
				printf("Specifica vertice sorgente:\n");
				scanf("%d",&u);
				printf("Specifica vertice di arrivo");
				scanf("%d",&v);
				Modifica_peso(G, n_peso, u, v);
				
				break;
			case 4:
				printf("Elimina arco specificando vertice sorgente e di arrivo:\n");
				printf("Specifica vertice sorgente:\n");
				scanf("%d",&u);
				printf("Specifica vertice di arrivo");
				scanf("%d",&v);
				
				G=remove(G, u, v);
				
				break;
			case 5:
				printf("Specificare il vertice per sapere il suo grado uscente\n");
				scanf("%d",&u);
				
					gu=grado_uscente(G, u);
			
				break;
			case 6:
				printf("Specificare il vertice per sapere il suo grado entrante\n");
				scanf("%d",&v);
				
					ge=grado_entrante(G, v);
				
					break;
			case 7:	
				peso_max=arco_peso_max(G);
				printf("Peso massimo = %d", peso_max);
				break;
			case 8:
				g_print(G);
		
		}
	
	}
	while(scelta==1 || scelta==2 || scelta==3 || scelta==4 || scelta==5 || scelta==6 || scelta==7 || scelta==8);
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
void Modifica_peso(graph *G, int n_peso, int u, int v){
	edge *e;
	e=G->adj[u];
	while(e!=NULL){
		if(e->key==v){
			e->peso = n_peso;
			
		}
		else
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
			//scorre la lista di adiacenza
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
void g_add(graph *G, int u, int v){ //u è il nodo da cui esce l'arco, v è il nodo in cui entra
	edge *new1, *e; 
	//Aggiungere frammento di codice per controlli vari
	new1 = (edge*)malloc(sizeof(edge));
	if (new1==NULL) 
		printf("ERRORE: impossibile allocare memoria \n");
	else {
		//Prepara il nodo da inserire nella lista di adiacenza del vertice u
		new1->key=v; 
		new1->next=NULL;
		
		if (G->adj[u] == NULL){ //u non ha archi
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



//Cancellazione arco
graph* remove(graph *G, int u, int v){
	edge *tmp;//è un puntatore quindi ha bisogno dell'asterisco
	edge *e;
	if(G->adj[u] != NULL){
		e=G->adj[u]; //assegna la testa della lista nella variabile e
		if(e->key==v){
			tmp=e;
			e=e->next;
			free(tmp);
		}
		else{ //se non è stato trovato l'elemento da eliminare
			G=remove(G, u, e->next->key);//il valore ritornato è un grafo quindi ritorna in G, e->next ritorna un valore edge, e->next->key un valore int
			
		}
	}
	return G;
}


void removeVertex(graph* G, int vertex) {
    edge* currNode;
    edge* prevNode;
    int i;

    // Rimuovi il vertice dalle liste di adiacenza dei suoi vicini
    for (i = 0; i < G->num_v; i++) {
        currNode = G->adj[i];
        prevNode = NULL;
        while (currNode != NULL) {
            if (currNode->key == vertex) {
                if (prevNode == NULL) { //se c'è un elemento
                    G->adj[i] = currNode->next; //la nuova testa è l'elemento successivo cioè NULL
                } else {
                    prevNode->next = currNode->next; //il successivo del precedete è il successivo del nodo attuale
                }
                free(currNode);
                break;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
    }

    // Rimuovi la lista di adiacenza del vertice
    currNode = G->adj[vertex];
    while (currNode != NULL) {
        edge* nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
    G->adj[vertex] = NULL;
}


//Calcolo grado uscente e entrante di un nodo (Grafo orientato)
int grado_uscente(graph *G, int u){
	edge *e;
	int gradousc=0;
	e=G->adj[u];
	while(e!=NULL){ //conta il numero di vertici a cui è collegato il vertice u
		gradousc++;
		e = e->next;
	}
	return gradousc;
}


int grado_entrante(graph *G, int v){
	edge *e;
	int gradoent=0;
	for(int i=0; i<G->num_v; i++){ //scorre l'array di indici
		e=G->adj[i];
		while(e!=NULL){
			if(e->key==v){ 
				gradoent++; //conta il numero di volte v compare in ciascuna lista di adiacenza
			}
			e = e->next;
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

//Calcolo dell arco con peso minore
int arco_peso_min(graph *G){
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

//Visita in profondità
void dfs(graph *g) {
	int i;
	//Alloca un array di appoggio per memorizzare quando un vertice è stato incontrato
	int *aux = (int*)calloc(g->num_v, sizeof(int)); 
	
	if(!aux) {
		printf("Errore di Allocazione\n");
	}
	else { 
		for(i = 0; i < g->num_v; i++){//Scorre i vertici del grafo
			if(aux[i] == 0) { //Se il vertice non è stato ancora incontrato
				printf("\n%d,",i); 
				dfs1(g,i,aux); //Chiama la funzione ricorsiva dfs1 su ogni vertice
			}
		}
		free(aux);//Dopo aver utilizzato l'array viene liberata la memoria dedicatagli
	}
}


void dfs1(graph *g, int i, int *aux) {
	edge *e; 
	aux[i] = 1;//aux[i] impostato ad uno perché il vertice corrente è stato appena visitato
	e = g->adj[i];
	
	while(e != NULL){ //Scorre i vertici adiacenti ad i
		if(aux[e->next->key] == 0) {//Se il vertice successivo non è stato visitato 
			printf("%d,",e->next->key); 
			dfs1(g,e->next->key,aux);//Chiamata ricorsiva sul vertice adiacente dell'adiacente
		}
		e = e->next;
	}
}


/*RIASSUNTO VISITA IN PROFONDITA'
	La visita in profondita parte da un vertice i e agisce ricorsivamente per visitare il vertice
	adiacente, l'adiacente dell'adiacente e così via fino ad arrivare al vertice che non ha 
	vertici adiacenti cioè il vertice di arrivo.
	Una volta raggiunto questo vertice si effettua la risalita della ricorsione e in quest'ultima
	per ogni vertice visitato si controllano i suoi adiacenti non visitati (aux[i]=1) (ammesso che li abbia) rieffettuando la ricorsione
	Tutto ciò viene fatto per ogni vertice. Cioè il for esterno fa si che ogni vertice venga considerato
	come vertice di partenza. Difatti il dfs è utile per calcolare il path minimo in un grafo.
*/


void bfs(graph *g) {
	int i, *aux = (int*)calloc(g->num_v,sizeof(int)); //allocazione di un'array con lunghezza num_v, inizializzando ciascuna posizione con valore 0
	if(aux == NULL) {
		printf("Errore di Allocazione\n");
	}
	else { 
		for(i = 0; i < g->num_v; i++){
			if(aux[i] == 0) { //se il nodo i non è stato visitato allora effettua la bfs
				printf("\n%d,",i+1); 
				bfs1(g,i,aux); 
			}
		}
		free(aux);
	}
}


void bfs1(graph *g, int i, int *aux) {
	edge *e;
	int Q[MAX+1]; //coda che gestisce gli elementi da visitare
	int *q = &Q[MAX+1];
	enqueue(q,i); //inserisce il nodo corrente nella coda
	
	while(!empty_queue(q)) {
		i = dequeue(q); //decoda il nodo corrente dalla coda
		aux[i] = 1; //segna il nodo corrente come visitato
		e = g->adj[i]; //memorizza la testa di una lista di adiacenza in e
		
		while(e!=NULL){ //scorre la lista di adiacenza
			if(aux[e->next->key] == 0){ //se il prossimo nodo, adiacente al nodo appena visitato, non è stato visitato
				enqueue(q,e->next->key); //inserisce il nuovo nodo nella coda
				printf("%d,",e->next->key); //stampa il nuovo nodo
				aux[e->next->key] = 1; //segna il nuovo nodo come visitato
			}
		}
	}
	destroyqueue(q);
}

/*RIASSUNTO VISITA IN AMPIEZZA
	La visita in ampiezza parte da un vertice i e utilizza una coda per memorizzare i vertici adiacenti.
	Una volta riempita, essa verrà decodata e utilizzerà l'elemento decodato come nuovo vertice, questo fino
	a quando la coda non è vuota.
	Ciò che viene fatto nello specifico è: 
		- visitare il nodo corrente scelto dal for in bfs
		- visitare tutti i nodi adiacenti al nodo corente e inserirli nella coda
		- visitare tutti i nodi adiacenti e per ognuno di loro inserire nella coda gli adiacenti
		- fino a quando la coda non è vuota ripetere il procedimento
		- quando la coda è vuota controlla se ci sono altri nodi on visitati con il for nella funzione bfs principale
*/

void enqueue(int Q[], int valore)
{
	Q[Q[MAX+1]] = valore;
	if (Q[0] == 0) 
		Q[0]=1; 
	Q[MAX+1] = (Q[MAX+1] % MAX) + 1; 
}


int dequeue(int Q[]) 
{
	int valore=Q[Q[0]];
	Q[0] = (Q[0] % MAX) + 1;
	if (Q[0] == Q[MAX+1]) {
		Q[0]=0; 
		Q[MAX+1]=1; 
	}
	return valore;
}

void destroyqueue(int Q[]){
	free(Q);
}


