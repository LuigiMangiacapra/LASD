/*Scrivere una funzione che, data una coda Q di interi con cardinalità pari, modifichi Q in modo che sostituisca ad ogni coppia di valori
consecutivi, la loro somma. La funzione restituisce la coda modificata*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void riempi_coda(int Q[], int n_elem);
void enqueue(int Q[], int elem);
int dequeue(int Q[]);
void stampa_queue(int Q[]);
void subst_cons_con_somma(int Q[]);

int main(){
	int n_elem;
	int Q[MAX + 2];
	
	printf("Inserisci numero pari di elementi\n");
	scanf("%d", &n_elem);
	
	while(n_elem % 2 != 0){
		printf("Il numero di elementi non e' pari\n");
		printf("Inserisci numero pari elementi\n");
		scanf("%d", &n_elem);
	}
	
	//Inizializza queue
	Q[0] = 0;
	Q[MAX+1] = 1;
	
	riempi_coda(Q, n_elem);
	stampa_queue(Q);
	
	
	printf("\n");
	
	
	subst_cons_con_somma(Q);
	stampa_queue(Q);
}


void riempi_coda(int Q[], int n_elem){
	int elem;
	if(n_elem != 0){
		printf("Inserici elemento\n");
		scanf("%d", &elem);
		enqueue(Q, elem);
		n_elem = n_elem - 1;
		riempi_coda(Q, n_elem);
	}
}


void enqueue(int Q[], int val){
	Q[Q[MAX+1]] = val;
	if(Q[0] == 0){
		Q[0] = 1;
	}
	Q[MAX+1] = (Q[MAX+1] % MAX) + 1;
}


int dequeue(int Q[]){
	int val = Q[Q[0]];
	Q[0] = (Q[0] % MAX) + 1;	
	if(Q[0] == Q[MAX+1]){
		Q[0] = 0;
		Q[MAX + 1] = 1;
	}
	return val;
}


void stampa_queue(int Q[]){
	int val;
	if(Q[0] != 0){
		val = dequeue(Q);
		printf("|%d| ", val);
		stampa_queue(Q);
		enqueue(Q, val);
	}
}


void subst_cons_con_somma(int Q[]){
	int val1;
	int val2;
	int somma;
	if(Q[0] != 0){
		val1 = dequeue(Q);
		val2 = dequeue(Q);
		somma = val1 + val2;
		subst_cons_con_somma(Q);
		enqueue(Q, somma);
		
	}
		
	
}


