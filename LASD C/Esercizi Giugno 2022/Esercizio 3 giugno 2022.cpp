/*
Scrivere una funzione che, dati due grafi G e H, verifichi se H è un sottografo di G.
Si ricorda che H = (V', E') si dice sottografo di G = (V, E) se V' sottoindieme di V 
e per ogni(u, v) appartenente a E', (u, v) appartenente ad E
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
void g_print(graph *G);
void g_add(graph *G, int u, int v);
int is_subgraph(graph *G1, graph *G2);


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
	
	
	
	if(is_subgraph(G1, G2)){
		printf("G1 e' un sottografo di G2\n");
	}
	else{
		printf("G1 non e' un sottografo di G2\n");
	}
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
		printf("l'arco uscente dal vertice %d non puo' essere inserito perché il vertice %d non esiste", u ,u);
		return;
	}

	new1 = (edge*)malloc(sizeof(edge));//crea spazio in memoria per il nodo puntato da new1
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


//funzione per controllare se G1 è sottografo di G2
int is_subgraph(graph *G1, graph *G2){
	//Variabili
	edge *g1, *g2;
	int is_subgraph = 0;
	int i = 0;
	int n_v, flag = 0;
	
	//Se G1 ha meno nodi di G2 già è un buon punto di partenza, altrimenti non è un sottografo per definizione
	if(G1->num_v <= G2->num_v){
		n_v = G1->num_v;
		is_subgraph = 1;
	}
	else{
		return 0;
	}
	
	//Scorre per il numero di vertici del sottografo
	while(i < n_v){
		g1 = G1->adj[i];//testa della singola lista di adiacenza del primo grafo

		while(g1 != NULL){//scorre le liste di adiacenza del primo grafo
			g2 = G2->adj[i];//testa della singola lista di adiacenza del secondo grafo
			flag = 0;//flag per indicare se la lista di adiacenza indica se il grafo è un sottografo
			
			while(g2 != NULL){//scorre le liste di adiacenza del secondo grafo
				if(g1->key == g2->key){//Se almeno un arco di G1 è presente in G2 allora G1 è potenzialmente un sottografo, quindi esce senza nemmeno controllare il resto
					flag = 1;
					break;
				}
				else{//Se non siamo usciti, vuol dire che non si è matchato nemmeno una volta. Quindi il grafo G1 non è un sottografo di G2
					flag = 0;
				}
				g2 = g2->next;//incremento lista di adiacenza
			}
			
			
			//QUESTO CONFRONTO VA FATTO NEL WHILE PERCHE' SE ALMENO UN ELEMENTO NON VIENE MATCHATO DEVE USCIRE E NON CONTINUARE I CONFRONTI TRAMITE return 0
			if(flag == 1){//Se flag == 1 vuol dire che per il momento abbiamo un sottografo, questo eprò va fatto per ogni lista di adiacenza e non vle solo per la prima.
		        		  //è imminente l'uscita con 0 se le altre liste di adiacenza non rispettano tale condizione
				is_subgraph = 1;
			}
			else{
				is_subgraph = 0;
				return is_subgraph;
			}
			g1 = g1->next;
		}
	
		i++;
	}
	
	
	return is_subgraph;

}

