#include <stdio.h>
#include <stdlib.h>


typedef struct edge{
	int value; //valore del vertice di arrivo
	struct edge * next;	
	//questa struttura identifica un arco, NON UN VERTICE!!!
	
}edge;

typedef struct graph {
	int nv;
	edge **adj; 
}graph;

graph * creaGrafo(int num_vertici);
void stampaGrafo(graph * G);
void addArco(graph * G, int from, int dest);
graph* deleteArco(graph * G, int u, int v);
void deleteVertex(graph* G, int vertex);


int main(){
	
	
	graph * G = NULL;
	
	int numero_vertici = 0;
	
	printf("inserisci numeri vertici: ");
	scanf("%d", &numero_vertici);
	
	G = creaGrafo(numero_vertici);	
	
	addArco(G, 1 , 2);
	addArco(G, 1, 3);
	addArco(G, 2, 3);

	addArco(G, 3, 4);
	addArco(G, 4, 1);
	addArco(G, 4, 2);
	
	stampaGrafo(G);
	printf("elimino il numero 0\n\n\n");
	
	//deleteArco(G,3, 4);
	deleteVertex(G, 0);
	
	
	stampaGrafo(G);
	
	

	return 0;
}


graph * creaGrafo(int num_vertici) {
	
	graph * newGraph = (graph *) malloc(sizeof(graph));
	int i = 0;
	
	if(newGraph) {
		
		//grafo creato correttamente
		newGraph->nv = num_vertici;
		
		//vettore di puntatori
		newGraph->adj = (edge **) malloc (num_vertici * sizeof(edge));
		
		for(i = 0; i < num_vertici; i++){
			newGraph->adj[i] = NULL;		
		}
	}
	else {
		perror("errore");
		exit(1);
	}
	
	
	return newGraph;
	
}


void stampaGrafo(graph * G) {
	int i = 0;
	
	for(i = 0; i < G->nv; i++) {
		printf("vertice numero %d :", i);
		edge * scorri = G->adj[i];
		while(scorri) {
			printf("%d-->", scorri->value);
			scorri = scorri->next;
		}
		printf("NULL");
		printf("\n");
	}
	
	return;
}

void addArco(graph * G, int from, int dest){
	
	//creiamo il vertice di destianzione
	edge * destination = (edge *) malloc(sizeof(edge));

	if(destination) {
		destination->value = dest;
		destination->next = NULL;
	}
	
	else {
		perror("errore\n");
		exit(1);
	}

		
	if(!G->adj[from]) {
		G->adj[from] = destination;
	}
	else {
		edge * scorri = G->adj[from];
		while(scorri->next) {
			scorri = scorri->next;
		}
		scorri->next = destination;
		
	}
	

	return; 
}


graph* deleteArco(graph * G, int u, int v){
	
	
	edge *tmp;//è un puntatore quindi ha bisogno dell'asterisco
	edge *e;
	if(G->adj[u] != NULL){
		e=G->adj[u]; //assegna la testa della lista nella variabile e
		if(e->value==v){
			tmp=e;
			e=e->next;
			free(tmp);
		}
		else{ //se non è stato trovato l'elemento da eliminare
			G=deleteArco(G, u, e->next->value);//il valore ritornato è un grafo quindi ritorna in G, e->next ritorna un valore edge, e->next->key un valore int
			
		}
	}
	return G;
}


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
    for(i = vertex; i < G->nv-1; i++) {
    	G->adj[i] = G->adj[i+1];
	}
    
        
    //sempre l'ultima posizione va a null
    G->adj[G->nv-1] = NULL;
    G->nv -= 1;
    G->adj = (edge **)realloc(G->adj, G->nv * sizeof(edge));
    
  
    //Rimuove l'elemento nelle liste di adiacenza degli altri vertici
    for(i = 0; i < G->nv; i++){
    	
	    deleteArco(G, i, vertex);
	}
	

}
