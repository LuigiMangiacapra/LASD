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
void deleteVertex(graph* G, int vertex);
void deleteArco(graph * G, int from, int dest);

int main(){
	graph *G;
	int scelta, u, v, n_peso, gu, ge, peso_max,n, massimo;
	
	do{
		printf("\nScagli l'operazione da svolgere\n");
		printf("1-Crea grafo, 2-Aggiungi_arco, 3-Mondifica_un_peso, 4-Cancella_arco, 5-Grado_uscente, 6-Grado_entrante, 7-Arco_con_peso_maggiore, 8-Stampa_grafo, 9-Elimina_vertice , 10-exit\n");
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
					printf("20 � il numero massimo di elementi da poter inserire\n");
				
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
				break;
			case 9:
				printf("Inserisci elemento da eliminare\n");
				scanf("%d", &v);
				deleteVertex(G, v);
		
		}
	
	}
	while(scelta==1 || scelta==2 || scelta==3 || scelta==4 || scelta==5 || scelta==6 || scelta==7 || scelta==8 || scelta==9);
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
			free(G);//Se non � possibile allocare memoria per la lista, il grafo non ha senso di esistere
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
void g_add(graph *G, int u, int v){ //u � il nodo da cui esce l'arco, v � il nodo in cui entra
	edge *new1, *e; 
	if(!G || u < 0 || u >= G->num_v || v < 0 || v >= G->num_v) {
        printf("parametri non validi\n");
        return;
    }

    //ci accertiamo che non esista gia
    edge * scorri = G->adj[u];
    while(scorri){
        if(scorri->key == v) {
            printf("arco gia esistente\n");
            return;
        }
        scorri = scorri->next;
    }
    
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



//Cancellazione arco ricorsiva
graph* remove(graph *G, int u, int v){
	edge *tmp;//� un puntatore quindi ha bisogno dell'asterisco
	edge *e;
	if(G->adj[u] != NULL){
		e=G->adj[u]; //assegna la testa della lista nella variabile e
		if(e->key==v){
			tmp=e;
			e=e->next;
			free(tmp);
		}
		else{ //se non � stato trovato l'elemento da eliminare
			G=remove(G, u, e->next->key);//il valore ritornato � un grafo quindi ritorna in G, e->next ritorna un valore edge, e->next->key un valore int
			
		}
	}
	return G;
}

/*
//Cancellazione arco iterativa
void deleteArco(graph * G, int from, int dest){
	if (from >= G->nv || from < 0 || dest >= G->nv || dest < 0) {
        // Uno o entrambi i vertici non esistono
        return;
    }
 
    // Cerca l'arco nell'elenco di adiacenza del vertice from
    edge* prev = NULL;
    edge* curr = G->adj[from];
    while (curr != NULL && curr->value != dest) {
        prev = curr;
        curr = curr->next;
    }
 
    if (curr == NULL) {
        // L'arco non esiste
        return;
    }
 
    if (prev == NULL) {
        // L'arco � il primo dell'elenco di adiacenza
        G->adj[from] = curr->next;
    } else {
        // L'arco non � il primo dell'elenco di adiacenza
        prev->next = curr->next;
    }
 
    // Libera la memoria dell'arco eliminato
    free(curr);
}
*/


void deleteVertex(graph* G, int vertex) {
    
    //vertex = veritce da eliminare
    int i = 0, j = 0;
     
    edge * currNode = G->adj[vertex];
    
    //caso lista propria
    //svuotiamo la sua lista di adiacenza
    while (currNode != NULL) {
        edge* tmp = currNode;
        currNode = currNode->next;
        free(tmp);
    }
    
 
    //riallochiamo il vettore
    for(i = vertex; i < G->num_v-1; i++) {
    	G->adj[i] = G->adj[i+1];
	}
    
        
    //sempre l'ultima posizione va a null
    G->adj[G->num_v-1] = NULL;
    G->num_v -= 1;
    G->adj = (edge **)realloc(G->adj, G->num_v * sizeof(edge));
    
  
    //Rimuove l'elemento nelle liste di adiacenza degli altri vertici
    for(i = 0; i < G->num_v; i++){
    	
    	edge* testa = G->adj[i];
    	if(testa != NULL){
    		//Caso elemento in testa
    		if(testa->key == vertex){
				G->adj[i] = testa->next;
			}
			//caso elemento centrale
			else {
				edge * scorri = testa;
				while(scorri->next) {
					if(scorri->next->key == vertex){
						testa = scorri->next;
						scorri->next = scorri->next->next;
						
					}
					else scorri = scorri->next;
				}
				
			}
			free(testa);
		}   
	}
	

}


//Calcolo grado uscente e entrante di un nodo (Grafo orientato)
int grado_uscente(graph *G, int u){
	edge *e;
	int gradousc=0;
	e=G->adj[u];
	while(e!=NULL){ //conta il numero di vertici a cui � collegato il vertice u
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
	int pesomax=100000;
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

//Visita in profondit�
void dfs(graph *g) {
	int i;
	//Alloca un array di appoggio per memorizzare quando un vertice � stato incontrato
	int *aux = (int*)calloc(g->num_v, sizeof(int)); 
	
	if(!aux) {
		printf("Errore di Allocazione\n");
	}
	else { 
		for(i = 0; i < g->num_v; i++){//Scorre i vertici del grafo
			if(aux[i] == 0) { //Se il vertice non � stato ancora incontrato
				printf("\n%d,",i); 
				dfs1(g,i,aux); //Chiama la funzione ricorsiva dfs1 su ogni vertice
			}
		}
		free(aux);//Dopo aver utilizzato l'array viene liberata la memoria dedicatagli
	}
}


void dfs1(graph *g, int i, int *aux) {
	edge *e; 
	aux[i] = 1;//aux[i] impostato ad uno perch� il vertice corrente � stato appena visitato
	e = g->adj[i];
	
	while(e != NULL){ //Scorre i vertici adiacenti ad i
		if(aux[e->next->key] == 0) {//Se il vertice successivo non � stato visitato 
			printf("%d,",e->next->key); 
			dfs1(g,e->next->key,aux);//Chiamata ricorsiva sul vertice adiacente dell'adiacente
		}
		e = e->next;
	}
}


/*RIASSUNTO VISITA IN PROFONDITA'
	La visita in profondita parte da un vertice i e agisce ricorsivamente per visitare il vertice
	adiacente, l'adiacente dell'adiacente e cos� via fino ad arrivare al vertice che non ha 
	vertici adiacenti cio� il vertice di arrivo.
	Una volta raggiunto questo vertice si effettua la risalita della ricorsione e in quest'ultima
	per ogni vertice visitato si controllano i suoi adiacenti non visitati (aux[i]=1) (ammesso che li abbia) rieffettuando la ricorsione
	Tutto ci� viene fatto per ogni vertice. Cio� il for esterno fa si che ogni vertice venga considerato
	come vertice di partenza. Difatti il dfs � utile per calcolare il path minimo in un grafo.
*/


void bfs(graph *g) {
	int i, *aux = (int*)calloc(g->num_v,sizeof(int)); //allocazione di un'array con lunghezza num_v, inizializzando ciascuna posizione con valore 0
	if(aux == NULL) {
		printf("Errore di Allocazione\n");
	}
	else { 
		for(i = 0; i < g->num_v; i++){
			if(aux[i] == 0) { //se il nodo i non � stato visitato allora effettua la bfs
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
			if(aux[e->next->key] == 0){ //se il prossimo nodo, adiacente al nodo appena visitato, non � stato visitato
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
	Una volta riempita, essa verr� decodata e utilizzer� l'elemento decodato come nuovo vertice, questo fino
	a quando la coda non � vuota.
	Ci� che viene fatto nello specifico �: 
		- visitare il nodo corrente scelto dal for in bfs
		- visitare tutti i nodi adiacenti al nodo corente e inserirli nella coda
		- visitare tutti i nodi adiacenti e per ognuno di loro inserire nella coda gli adiacenti
		- fino a quando la coda non � vuota ripetere il procedimento
		- quando la coda � vuota controlla se ci sono altri nodi on visitati con il for nella funzione bfs principale
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


