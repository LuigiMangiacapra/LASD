#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "Graph.h"


Graph initGraph(int nodes_count) {
    Graph G = (Graph)malloc(sizeof(struct TGraph));//alloca in memoria la struct del grafo
    G->adj = (List *)calloc(nodes_count, sizeof(List));//attraverso la struct del grafo alloca in memoria la lista nel campo adj di graph, 
													   //ciò permette di collegare le liste di adiacenza all'array che le contiene, inoltre calloc alloca più spazi in memoria 
													   //consecutivi e li istanzia col valore 0
    G->nodes_count = nodes_count;
    return G;
}

Graph randomGraph(int nodes, int edges_min, int edges_max) {
    Graph G = initGraph(nodes);
	int i = 0;
    int x = 0;
    int y = 0;
    int target=0;
    srand((unsigned int)time(NULL));
    assert( edges_min <= edges_max ); // non possono esserci edges_min > edges_max
    if (edges_max > nodes) {
        edges_max = nodes - 1;
    }
    if(nodes>1) { //senza questo controllo,in un grafo con un nodo aggiungeva un arco con target -1
    	for (i = 0; i < nodes; i++) {
       		for (x = 0; x < edges_min; x ++) {
       		 	target=rand()%nodes;
        		if(target==i) //un non ha archi ricorsivi
        			target++;
        		if(target==nodes) //se nell'incremento il target Ã¨ un nodo che non esiste lo decremento di due
        			target-=2;
        	    addEdge(G, i, target, rand() % 50);
        	}
        	if(edges_min<edges_max)//   crash se edges_min==edges_max  (rand()%0),quindi non aggiunge ulteriori nodi
        	{
        		for (y = 0; y < rand() % (edges_max - edges_min); y++) {
        		    target=rand()%nodes;
					if(target==i) //un non ha archi ricorsivi
						target++;
					if(target==nodes) //se nell'incremento il target Ã¨ un nodo che non esiste lo decremento di due
						target-=2;
					addEdge(G, i, target, rand() % 50);
        		}
        	}
    	}
    }
    return G;
}

//Elimina il grafo(componente per componente)
void freeGraph(Graph G) {
    if (G != NULL) {
        if (G->nodes_count > 0) {
            int i = 0;
            for (i = 0; i < G->nodes_count; i++) {
                freeList(G->adj[i]);//svuota le liste in ogni locazione dell'array
            }
        }
        free(G);
    }
}


//Stampa il grafo
void printGraph(Graph G) {
    if (G != NULL) {
        int x = 0;
        for (x = 0; x < G->nodes_count; x++) {
            printf("%d -> ", x);
            printList(G->adj[x]);//In G->adj abbiamo allocato la memoria della lista, x indica su quale vertice vogliamo navigare sugli adiacenti
            printf("\n");		 //Tramite G->adj (su cui abbiamo allocato con calloc quindi avrà più locazioni di memoria consecutive)accediamo direttamente
								 //ad un array di liste creato dalla calloc 
        }
    }
}


//Aggiunta Arco
void addEdge(Graph G, int source, int target, int peso) {//prende il grafo, il nodo da cui parte l'arco, il nodo in cui entra l'arco e il peso dell'arco
    assert(G != NULL);//Da errore se è falsa l'espressione (es° se G == NULL da errore)
    assert(source < G->nodes_count);//se il vertice di partenza non è minore al numero di vertici lancia errore
    assert(target < G->nodes_count);//se il vertice di arrivo non è minore al numero di vertici lancia errore
    if (source != target) {//non ci devono essere cappi
        G->adj[source] = appendNodeList(G->adj[source], target, peso);//Aggiunge elemento in coda alla lista in posizione source-esima
	}//G->adj[source] ci permette di accedere all'array della lista di adiacenza, tramite le parentesi quadre accediamo alla lista i-esima nell'array creato tramite calloc
     //La calloc permette di allocare anche più spazi di memoria consecutivi, inizializzati a 0
}

//NOTA BENE: QUANDO SI AGGIUNGE UN ARCO LO SI AGGIUNGE SU VERTICI GIA' ESISTENTI, CHE PARTE DAL VERTICE source E CHE SI COLLEGHI AL target


List removeEdge(Graph G, int source, int target) {
    assert(G != NULL);//leggi addEdge
    assert(source < G->nodes_count);//Leggi addEdge
    assert(target < G->nodes_count);//Leggi addEdge
    if (source != target) {
        G->adj[source] = removeNodeList(G->adj[source], target);
    }
	return G->adj[source];//restituisce rimosso
}


void addNode(Graph G) {
    if (G != NULL) {
        G->adj = (List *)realloc(G->adj, (G->nodes_count+1) * sizeof(List));//poiché aggiungendo un nodo cambia anche il campo nodes_count di graph bisogna riallocare memoria
        G->nodes_count += 1;
        G->adj[G->nodes_count-1] = NULL;//poiché è stato appena inserito un nuovo vertice, questo non avrà valore quindi va inizializzato con NULL
    }
}
//NOTA BENE: QUANDO SI AGGIUNGE UN NUOVO NODO NON SI CONSIDERA FIN DA SUBITO L'ARCO CHE GLI PERMETTE DI ESSERE COLLEGATO AL GRAFO CORRISPONDENTE
//			 UN NODO PUò ESSERE ANCHE SCOLLEGATO DAL RESTO DEL GRAFO, INOLTRE PER INSERIRNE UNO NUOVO BISOGNA MODIFICARE L'ARRAY DEI VERTICI E RIALLOCARE MEMORIA SU QUEST'ULTIMO
//           E' COME INSERIRE UN NUOVO ELEMENTO IN UN ARRAY PIENO, BISOGNA CREARNE UNO NUOVO E INSERIRCI I VECCHI ELEMENTI PIU' QUELLO NUOVO


//Rimuove un vertice del grafo
void removeNode(Graph G, int node_to_remove) {
    if (G != NULL) {
        int i = 0;
        int x = 0;
        List *tmp = G->adj;//tmp punta l'array
        //la calloc prende in input il numero di elementi da allocare e la grandezza del singolo
        G->adj = (List *)calloc(G->nodes_count-1, sizeof(List));//alloca memoria riducendo di uno il numero di vertici nel grafo(perché ne verrà eliminato uno-)
        for (i = 0; i < G->nodes_count; i++) {//scorre l'array
            if (i != node_to_remove) {//se il vertice da eliminare non è il corrente
                G->adj[x] = checkListRemoval(tmp[i], node_to_remove);//anche se il vertice non è stato ancora trovato, iniziamo ad eliminarlo nelle liste di adiacenza degli altri
                x++;//indice dell'array								 //l'operazione di eliminazione nelle liste di adiacenza viene svolta dalla funzione checkListRemoval
            } else {
                freeList(G->adj[x]);//se l'elemento è stato trovato chiama la funzione freeList che permette di eliminare totalmente una lista in una posizione dell'array
                					//così facendo si elimina completamente il vertice comprendendo l'eliminazione di quest'ultimo nelle liste di adiacenza degli altri vertici
            }
        }
        free(tmp);//perché tmp? perché è l'unico puntatore che punta all'array e poiché non serve più va lberato
        G->nodes_count -= 1;//decrementa nodes_count di graph in quanto è stato appena eliminato un vertice
    }
}

//rimuove l'elemento dalle liste di adiacenza e ristabilisce l'ordine tra i nodi
List checkListRemoval(List L, int node_to_remove) {
    if (L != NULL) {
        L->next = checkListRemoval(L->next, node_to_remove);
        if (L->target == node_to_remove) {//Se l'elemento da eliminare è stato trovato nella lista
            List tmp = L->next;//tmp punta al successivo dell'elemento da eliminare
            free(L);//libera memoria sull'elemento da eliminare
            return tmp;
            
        } else if (L->target > node_to_remove) {// controlla se l'elemento corrente è maggiore da quello da eliminare perché si risale dalla ricorsione e quindi da vertici successivi
            L->target -= 1;							//Se il nodo è successivo a quello da eliminare, decrementa il suo indice che rappresenta il nodo i-esimo
            										//Es° 1->2->3->4->5->NULL  se vogliamo eliminare 3 allora si chiama ricorsivamente fino a 5 e si decrementa ciascun target
            										//ecco la successione di operazioni:  a) 1->2->3->4->4->NULL  b)1->2->3->3->4->NULL  c)1->2->3->4->NULL  3 eliminato e ordine ristabilito
        }
    }
    return L;
}


//Creazione di una matrice trasposta a partire da una matrice iniziale (questo consideranto due array src e dst)
void transpose(float *src, float *dst, const int N, const int M) {
    //n si sposta per tutta la matrice perché la lunghezza della matrice è N*M (righe*colonne)
    for(int n = 0; n<N*M; n++) {
    	//i è un valore intero rcavato da n/N che convertito in intero è sempre 0 a meno che n=N
        int i = n/N;
        //j è un valore che va da 0 a N perché n%N darà come risultato o il minimo di n (0) oppure massimo N-1
        int j = n%N;
        //dst conterrà tutti i valori di src trasposti
        /*Ma come viene effettuata la trasposizione?
        	-M è un valore fisso ed è la lunghezza delle colonne
        	-j ed i variano grazie all'ausilio di n
        		-Nello specifico i è quasi sempre 0 e j permette di scorrere la singola riga dando come limite N (lunghezza di una singola riga)
        */	
        dst[n] = src[M*j + i];
        /*
        Specifiche di M*j+1:
        	- M*j+1 con M=5 può assumere questi valori:
        		- 0-5-10-15 e poi si ripete, inoltre quando j=0 cioè n=N allora i=1 
        		- Questo significa che prendiamo solo i valori della prima colonna e li inseriamo nella prima riga di dst
        		  sempre in maniera metaforica visto che sono array
        		- In sintesi, M rappresenta la lunghezza di ogni riga e j la singola colonna
        		
        		Es°
        		1 0 1 0 0     ------>    1 0 1 0 0 0 1 0 1 1
        		0 1 0 1 1
        		
        		M rappresenta la lunghezza di ogni colonna cioè 5 e j rappresenta la singola riga
        		La prima volta si prenderanno solo i valori  1 e 0  e quando verranno inseriti nell' array di destinazione, essi saranno parte della sua prima riga
		*/
    }
}

