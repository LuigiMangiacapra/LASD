/*
	- Vedere BFS e DFS 	V
	- Vedere componenti fortemente connesse V
	- Vedere grafo completo V
	- Vedere unione, intersezione, differenza tra grafi
	- Vedere nozione di sottografo
	- Vedere l'algoritmo di Dijkstra (per trovare minimo)	V
	- Grafi con matrici di adiacenza
*/

#include <stdio.h>
#include <stdlib.h>

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
void g_add(graph *G, int u, int v, int peso);
void dfs(struct graph *g);
void dfs1(struct graph *g, int i, int *aux);
void bfs(struct graph *g);
void bfs1(struct graph *g, int i, int *aux);
void enqueue(int Q[], int valore);
int dequeue(int Q[]);
void destroyqueue(int Q[]);
void dijkstra(graph* G, int start);
void strongly_connected_components(graph* g);
graph* create_transpose(graph* g);
void destroy_graph(graph* G);
void dfs_t(graph *g, int* aux);
void dfs1_t(graph *g, int i, int *aux);
void complete_graph(graph* G);


int main(){
	graph *G;
	int scelta, u, v, n_peso, gu, ge, peso_max,n, massimo;
	int i = 0;
	int n_elem = 0;
	int start = 0;
	int peso;
	
	printf("Quanti vertici vuoi inserire?\n");
	scanf("%d", &n);
	if(n<MAX){
		G=crea_grafo(n);
		printf("Grafo vuoto creato\n");
	}
	else
		printf("20 è il numero massimo di elementi da poter inserire\n");
				
	printf("Quanti archi vuoi inserire?\n");
	scanf("%d", &n_elem);
	
	while(i < n_elem){
		printf("Aggiungi arco specificando vertice sorgente e di arrivo:\n");
		printf("Specifica vertice sorgente:\n");
		scanf("%d",&u);
		printf("Specifica vertice di arrivo\n");
		scanf("%d",&v);
		printf("Specifica peso\n");
		scanf("%d",&peso);
		g_add(G, u, v, peso);
		i++;
	}
	
	printf("Stampa grafo\n");
	g_print(G);
	
	printf("\nAlgoritmo di Dijkstra per trovare il minimo\n");
	dijkstra(G, start);
	
	printf("\nAlgoritmo di Tarjan sulle componenti fortemente connesse\n");
	strongly_connected_components(G);
	
	printf("\nControlliamo se il grafo e' completo\n");
	complete_graph(G);
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
void g_add(graph *G, int u, int v, int peso){ //u è il nodo da cui esce l'arco, v è il nodo in cui entra
	edge *new1, *e; 
	if(!G || u < 0 || u >= G->num_v || v < 0 || v >= G->num_v || peso < 0) {
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
		new1->peso = peso;
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



//Visita in profondità
void dfs(graph *g) {
	int i;
	//Alloca un array di appoggio per memorizzare quando un vertice è stato incontrato
	int *aux = (int*)calloc(g->num_v, sizeof(int)); 
	
	if(!aux) {
		perror("Errore di Allocazione");
		exit(1);
	}
	else { 
		for(i = 0; i < g->num_v; i++){//Scorre i vertici del grafo, serve se il grafo non è connesso, quindi diviso in più sottografi !!!
			if(aux[i] == 0) { //Se il primo vertice di ogni grafo sconnesso o dell'unico grafo se completamente connesso non è stato visitato
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
		if(aux[e->key] == 0) {//Se il vertice successivo non è stato visitato 
			dfs1(g,e->key,aux);//Chiamata ricorsiva sul vertice adiacente dell'adiacente
		}
		e = e->next;
	}
}


/*RIASSUNTO VISITA IN PROFONDITA'
	La visita in profondita parte da un vertice i e agisce ricorsivamente per visitare il vertice
	adiacente, l'adiacente dell'adiacente e così via fino ad arrivare al vertice che non ha 
	vertici adiacenti cioè il vertice di arrivo.
	Una volta raggiunto questo vertice si effettua la risalita della ricorsione e in quest'ultima
	per ogni vertice rivisitato si controllano i suoi adiacenti non visitati (aux[i]==0) (ammesso che li abbia) rieffettuando la ricorsione
	Il for esterno serve soltanto per grafi non direttamente connessi, quindi separati in più sottovertici.
	
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
	int Q[MAX+2]; //coda che gestisce gli elementi da visitare
	int *q = &Q[MAX+2];
	enqueue(q,i); //inserisce il nodo corrente nella coda
	
	while(!empty_queue(q)) {
		i = dequeue(q); //decoda il nodo corrente dalla coda
		aux[i] = 1; //segna il nodo corrente come visitato
		e = g->adj[i]; //memorizza la testa di una lista di adiacenza in e
		
		while(e!=NULL){ //scorre la lista di adiacenza
			if(aux[e->key] == 0){ //se il prossimo nodo, adiacente al nodo appena visitato, non è stato visitato
				enqueue(q,e->key); //inserisce il nuovo nodo nella coda
				printf("%d,",e->key); //stampa il nuovo nodo

			}
			e = e->next;
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
		- quando la coda è vuota controlla se ci sono altri nodi non visitati con il for nella funzione bfs principale
	Inoltre il bfs è utile per calcolare il path minimo in un grafo.
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


void dijkstra(graph* G, int start) {
    int i, min_v, v;
    int* distance = (int*)malloc(G->num_v * sizeof(int)); //Memorizza la distanza
    int* visited = (int*)malloc(G->num_v * sizeof(int)); //Memorizza lo stato di visita
    int* prev = (int*)malloc(G->num_v * sizeof(int)); //Memorizza il nodo precedente nel percorso più breve per ogni vertice

	//Inizializza le strutture
    for (i = 0; i < G->num_v; i++) {
        distance[i] = INT_MAX; //Distanza quasi infinita iniziale per ogni vertice
        visited[i] = 0; //Imposta tutti i vertici come non visitati, impostando i valori dell'array visited a 0
        prev[i] = -1; 
    }

	//Imposta la distanza iniziale a 0
    distance[start] = 0; 

	
	//itera attraverso tutti i vertici del grafo (NUCLEO FONDAMENTALE DELLA FUNZIONE!)
    for (i = 0; i < G->num_v; i++) {
        min_v = -1;

        // Trova il nodo non visitato con la distanza minima
        for (v = 0; v < G->num_v; v++) {
        	//printf("Distanza_min: %d e distanza_v: %d PRIMA\n", distance[min_v], distance[v]);
        	//La condizione che si analizza inizialmente è (visited[v) == 0 && u == -1) poiché non si può accedere a distanze con u = -1
            if (visited[v] == 0 && (min_v == -1 || distance[v] < distance[min_v])) //il vertice minimo non sarà sempre il primo, perché quando sarà visitato non si entrerà più nell'if in quel caso
                min_v = v; //min_v è il vertice con distanza minima dal vertice di origine
                
            //printf("Distanza_min: %d e distanza_v: %d DOPO\n", distance[min_v], distance[v]);
        }
    	//printf("Distanza: %d\n", distance[min_v]);

        if (distance[min_v] == INT_MAX) //Se la distanza del nodo u è ancora INT_MAX, significa che non ci sono ulteriori nodi raggiungibili nel grafo e l'algoritmo termina prematuramente con il comando break.
            break;

        visited[min_v] = 1; //Il vertice u è visitato

        // Aggiorna le distanze dei nodi adiacenti al nodo selezionato
        edge* e = G->adj[min_v];
        while (e != NULL) {
            v = e->key;
            int weight = e->peso;
            int newDistance = distance[min_v] + weight; //Aggiunge al valore della distanza minima il peso di un arco
            
            if (newDistance < distance[v]) { //Questo controllo serve a sostituire la distanza "infinita"/INT_MAX con un valore vero e proprio calcolato dal peso dell'arco che lo precede
                distance[v] = newDistance;
                prev[v] = min_v;
            }
            e = e->next;
        }
    }

    // Stampa i risultati
    for (i = 0; i < G->num_v; i++) {
        if (distance[i] == INT_MAX) //Caso di vertici scollegati
            printf("Distanza dal nodo %d al nodo %d: Infinito\n", start, i);
        else {
            printf("Distanza dal nodo %d al nodo %d: %d\n", start, i, distance[i]);
            printf("Percorso minimo: ");
            int current = i;
            while (current != start) {
                printf("%d <- ", current);
                current = prev[current];
            }
            printf("%d\n", start);
        }
    }

    free(distance);
    free(visited);
    free(prev);
}


/*Riassunto Dijkstra
	1. Viene dichiarata la funzione dijkstra che prende due parametri: un puntatore a una struttura graph rappresentante il grafo e un intero start che indica il nodo di partenza.

	2. Vengono dichiarate e inizializzate le variabili i, u e v utilizzate come indici per iterazioni.
	
	3. Vengono dichiarati tre array dinamici: distance, visited e prev. Questi array sono inizializzati con dimensione pari al numero di vertici del grafo G->num_v e vengono utilizzati per memorizzare la distanza, lo stato di visita e il nodo precedente nel percorso più breve per ogni vertice.
	
	4. Viene eseguito un ciclo for per inizializzare le strutture. Per ogni vertice i nel grafo, viene impostata la distanza a INT_MAX (un valore molto grande) per rappresentare una distanza infinita iniziale. Inoltre, tutti i vertici vengono impostati come non visitati (visited[i] = 0) e il nodo precedente viene impostato a -1 (prev[i] = -1).
	
	5. La distanza del nodo di partenza (start) viene impostata a 0 (distance[start] = 0), poiché la distanza da un nodo a se stesso è sempre 0.
	
	6. Viene eseguito un altro ciclo for per iterare attraverso tutti i vertici del grafo. All'interno di questo ciclo, viene cercato il nodo non visitato con la distanza minima. La variabile u viene inizializzata a -1 e successivamente viene aggiornata al valore del vertice v se v è non visitato e ha una distanza minore di u o se u è ancora -1. In pratica, questa parte del codice trova il vertice più vicino e non visitato tra quelli rimanenti.
	
	7. Se la distanza del nodo u è ancora INT_MAX, significa che non ci sono ulteriori nodi raggiungibili nel grafo e l'algoritmo termina prematuramente con il comando break.

	8. Il nodo u viene contrassegnato come visitato impostando visited[u] = 1.
	
	9. Viene eseguita un'iterazione su tutti gli archi adiacenti al nodo u utilizzando un puntatore e che punta alla lista di adiacenza del nodo u. Viene esaminato ogni arco per calcolare una nuova distanza per il nodo adiacente v rispetto al nodo u. Se la nuova distanza calcolata (newDistance) è minore della distanza attualmente memorizzata per v, allora la distanza viene aggiornata a newDistance e il nodo precedente per v viene impostato a u. Questo passaggio consente di individuare il percorso più breve tra il nodo di partenza e tutti gli
*/


graph* create_transpose(graph* g) {
    graph* transpose = crea_grafo(g->num_v); // Crea un nuovo grafo vuoto con lo stesso numero di vertici

    int i, j;
    for(i = 0; i < g->num_v; i++) {
        // Scorre la lista di adiacenza di ogni vertice nel grafo originale
        edge* current = g->adj[i];
        while(current != NULL) {
            // Aggiunge un arco dal vertice corrente al vertice i nel grafo trasposto
            g_add(transpose, current->key, i, current->peso);
            current = current->next;
        }
    }

    return transpose;
}

//Visita in profondità
void dfs_t(graph *g, int* aux) {
	int i;
	
	if(!aux) {
		perror("Errore di Allocazione");
		exit(1);
	}
	else { 
		for(i = 0; i < g->num_v; i++){//Scorre i vertici del grafo, serve se il grafo non è connesso, quindi diviso in più sottografi !!!
			if(aux[i] == 0) { //Se il primo vertice di ogni grafo sconnesso o dell'unico grafo se completamente connesso non è stato visitato
				printf("\nLa seguente componente fortemente connessa con questi nodi: |%d|", i);
				dfs1_t(g,i,aux); //Chiama la funzione ricorsiva dfs1 su ogni vertice
			}
		}
		free(aux);//Dopo aver utilizzato l'array viene liberata la memoria dedicatagli
	}
}


void dfs1_t(graph *g, int i, int *aux) {
	edge *e; 
	aux[i] = 1;//aux[i] impostato ad uno perché il vertice corrente è stato appena visitato
	e = g->adj[i];
	
	while(e != NULL){ //Scorre i vertici adiacenti ad i
		
		if(aux[e->key] == 0) {//Se il vertice successivo non è stato visitato 
			printf(" |%d|", e->key);
			dfs1_t(g,e->key,aux);//Chiamata ricorsiva sul vertice adiacente dell'adiacente
		}
		
		e = e->next;
	}
}

void strongly_connected_components(graph* g) {
    int i;
    int* visited = (int*)calloc(g->num_v, sizeof(int));
    graph* transpose = create_transpose(g);
	
    // Visita in profondità sul grafo originale
    dfs(g);

    // Resetta l'array visited
    for (i = 0; i < g->num_v; i++) {
        visited[i] = 0;
    }

    // Visita in profondità sul grafo trasposto
    dfs_t(transpose, visited);

    destroy_graph(transpose);
}



void destroy_graph(graph* G) {
    if (G != NULL) {
        // Dealloca le liste di adiacenza
        for (int i = 0; i < G->num_v; i++) {
            edge* e = G->adj[i];
            while (e != NULL) {
                edge* next = e->next;
                free(e);
                e = next;
            }
        }
        // Dealloca l'array di puntatori alle liste di adiacenza
        free(G->adj);
        // Dealloca la struttura del grafo
        free(G);
    }
}



void complete_graph(graph* G){
	int i;
	int count_edges;
	int flag = 1;
	edge* e;
	
	for(i = 0; i < G->num_v; i++){
		count_edges = 0;
		e = G->adj[i];
		
		while(e != NULL){
			count_edges++;
			e = e->next;
		}
		
		if(count_edges != (G->num_v-1)){
			printf("Il grafo non e' completo\n");
			flag = 0;
			break;	
		}
	}
	
	
	if(flag == 1){
		printf("Il grafo e' completo\n");
	}
	else{
		return;
	}
}

