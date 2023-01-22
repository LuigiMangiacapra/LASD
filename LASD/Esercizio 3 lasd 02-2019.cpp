/*
Dati due grafi orientati e pesati scrivi una funzione che presi H e G restituisce G
con i pesi dei suoi archi diminuiti dei pesi degli archi corrispondenti in H. Se
un arco ha peso minore di 10 lo si elimina. Descrivi la complessità.
*/

typedef struct edge{
	int key;
	struct edge *next;
	int peso;
	
}edge;


typedef struct graph{
	int nv;
	edge** adj;
	
}graph;


graph* crea_grafo(int n);
void g_print(graph *G);
void g_add(graph *G, int u, int v);
graph* remove(graph *G, int u, int v);
int arco_peso_max(graph *G);

graph* function(graph* H, graph* G);//restituisce G aggiornata riducendo i pesi di ciascun arco con i pesi dell'altro grafo

int main(){
	int scelta;
	do{
		printf("Che operazione vuoi eseguire?\n");
		printf("1-crea_grafo, 2-aggiungi_arco, 3-rimuovi_arco, 4-funzione_esercizio, 5-stampa, 6-esci\n");
		scanf("%d",&scelta);
		switch(scelta){
			case 1:
			break;
			
			case 2:
			break;
			
			case 3:
			break;
			
			case 4:
			break;
			
			case 5:
			break;
		
		}
	
	}
	while(scelta==1 || scelta==2 || scelta==3 || scelta==4 || scelta==5);

}


graph* crea_grafo(int n){
	graph* G;
	G=(graph*)malloc(sizeof(graph*));
	if(G==NULL)
		printf("Impossibile allocare memoria!\n");
	else{	
		G->adj=(edge**)malloc(sizeof(edge**));
		if(G->adj==NULL){
			printf("Impossibile allocare memoria!\n");
			free(G);
			G==NULL;
		}
		else{
			for(int i=0; i<n; i++){
				G->adj[i]=NULL;
			}
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
		printf("\n il grafo ha %d vertici\n",G->num_v);
		for(i=0;i<G->num_v;i++){
			printf("nodi adiacenti al nodo %d",i);
			e=G->adj[i];
			while(e!=NULL){
				printf("%d",e->key);
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
	new1 = (edge*)malloc(sizeof(edge));
	if (new1==NULL) printf("ERRORE: impossibile allocare memoria \n");
	else {
		new1->key=v; 
		new1->next=NULL;
		if (G->adj[u] == NULL) //u non ha archi //
			G->adj[u] = new1;
		else {
			e=G->adj[u];
			while(e->next!=NULL)
				e=e->next; 
			} 
			e->next=new1;
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

