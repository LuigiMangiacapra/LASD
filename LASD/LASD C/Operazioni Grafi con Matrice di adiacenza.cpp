//Grafi con matrici di adiacenza

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20
#define MAXROW 20
#define MAXCOL 20


//PROTOTIPI
int* crea_grafo(int matrix[MAXROW][MAXCOL]);
void g_print( int row, int column, int matrix[MAXROW][MAXCOL]);
void g_add(int row, int column , int matrix[MAXROW][MAXCOL], int u, int v);
int* remove(int row, int column, int matrix[MAXROW][MAXCOL],  int u, int v);

/*void Modifica_peso(graph *G, int n_peso,int u, int v);
int grado_uscente(graph *G, int u);
int grado_entrante(graph *G, int v);
int arco_peso_max(graph *G);
*/


int main(){
	int matrix[MAXROW][MAXCOL];
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
					matrix=crea_grafo(matrix);
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
				g_add(matrix, n, n, u, v);
				
				break;
			case 3:/*
				printf("Modifica il peso di un arco specificando peso,vertice sorgente e di arrivo\n");
				printf("Specifica peso modificante\n");
				scanf("%d",&n_peso);
				printf("Specifica vertice sorgente:\n");
				scanf("%d",&u);
				printf("Specifica vertice di arrivo");
				scanf("%d",&v);
				
				Modifica_peso(G, n_peso, u, v);*/
			
				break;
			case 4:
				printf("Elimina arco specificando vertice sorgente e di arrivo:\n");
				printf("Specifica vertice sorgente:\n");
				scanf("%d",&u);
				printf("Specifica vertice di arrivo");
				scanf("%d",&v);
				
				matrix=remove(matrix, n, n, u, v);
				
				break;
			case 5:
				/*printf("Specificare il vertice per sapere il suo grado uscente\n");
				scanf("%d",&u);
				
					gu=grado_uscente(G, u);
			*/
				break;
			case 6:/*
				printf("Specificare il vertice per sapere il suo grado entrante\n");
				scanf("%d",&v);
				
					ge=grado_entrante(G, v);
				*/
					break;
			case 7:	/*
				peso_max=arco_peso_max(G);
				printf("Peso massimo = %d", peso_max);*/
				break;
			case 8:
				g_print(matrix, n, n);
		
		}
	
	}
	while(scelta==1 || scelta==2 || scelta==3 || scelta==4 || scelta==5 || scelta==6 || scelta==7 || scelta==8);
}



//creazione grafo vuoto (senza le varie liste di adiacenza)
int* crea_grafo(int matrix[MAXROW][MAXCOL]){//prende in input il numero di vertici per assegnarli successivamente alla struttura
	int i, j;
	int *matrixloc = *matrix;
	for(i=0; i<MAXROW; i++){
		for(j=0; j<MAXCOL; j++){
			matrixloc[i][j]=0;
		}
	}
	
	return matrixloc;
}



//Aggiunge arco
void g_add(int row, int column, int matrix[MAXROW][MAXCOL], int u, int v){//u è il nodo da cui esce l'arco, v è il nodo in cui entra
	
	int *matrixloc = *matrix;	
	matrixloc[u][v] = 1;
	
	
	return matrixloc;
}


//Aggiunge arco
int* remove(int row, int column, int matrix[MAXROW][MAXCOL], int u, int v){//u è il nodo da cui esce l'arco, v è il nodo in cui entra
	
	int *matrixloc = *matrix;	
	matrixloc[u][v] = 0;
	
	
	return matrixloc;
}


void g_print(int row, int column, int matrix[MAXROW][MAXCOL]){
	int i, j;
	int *matrixloc = *matrix;
	
	for(i=0; i<MAXROW; i++){
		printf("nodi adiacenti al nodo %d:", i);
		for(j=0; j<MAXCOL; j++){
			printf(" %d", matrixloc[i][j]);
		}
	}	


}

