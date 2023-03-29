#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void enqueue(int Q[], int new_value);
int dequeue(int Q[]);
void inizializza_queue(int Q[]);
void print_queue(int Q[]);
void funzione_somma(int Q[]);
void elimina_posizione_pari(int Q[]);
void somma_adiacenti(int Q[]);

int main() {
	
	int Q[MAX+2]; //creo la coda
	inizializza_queue(Q);
	int numero_elementi = 0, i = 0;
	
	//cardinalità pari
	do{
		printf("quanti (pari):");
		scanf("%d", &numero_elementi);
	}
	while(numero_elementi % 3 != 0);
	
	
	for(i = 0; i < numero_elementi; i++) {
		int elemento;
		printf("inserisci:");
		scanf("%d", &elemento);
		enqueue(Q, elemento);
	}
	
	print_queue(Q);
	
	//funzione_somma(Q);
	//elimina_posizione_pari(Q);
	somma_adiacenti(Q);
	printf("coda after somma\n\n");
	print_queue(Q);
	
	
	return 0;
	
}

void inizializza_queue(int Q[]){
	Q[0] = 0;//elemento a sinistra
	Q[MAX + 1] = 1;//ultima locazione libera
}

void enqueue(int Q[], int new_value) {
	
	Q[Q[MAX+1]] = new_value;
	if(Q[0] == 0) Q[0] = 1;
	Q[MAX+1] = (Q[MAX + 1] % MAX) + 1;
	
}

int dequeue(int Q[]) {
	int ret = Q[Q[0]];
	Q[0] = (Q[0] % MAX) + 1;
	if(Q[0] == Q[MAX + 1]){
		Q[0] = 0;
		Q[MAX + 1] = 1;
	}
	
	return ret;
}

void print_queue(int Q[]) {
	
	if(Q[0] == 0) return;
	int num = dequeue(Q);
	printf("%d | ", num);
	print_queue(Q);
	enqueue(Q, num);
}



void funzione_somma(int Q[]) {
	
	if(Q[0] == 0) return;
	int num = dequeue(Q);
	int num2 = dequeue(Q);
	int somma = num + num2;
		
	funzione_somma(Q);
	enqueue(Q, somma);
}


void elimina_posizione_pari(int Q[]) {
	if(Q[0] == 0) return;
	int indice = Q[0];
	int num = dequeue(Q);
	
	elimina_posizione_pari(Q);
	
	if(indice % 2 == 0) enqueue(Q, num); 
}


void somma_adiacenti(int Q[]) {
	if(Q[0] == 0) return;
	
	
	int num = dequeue(Q);
	
	int indice = Q[0];
	int num2 = dequeue(Q);
	
	int num3 = dequeue(Q);
	
	int somma = num + num3;

	somma_adiacenti(Q);
	
	enqueue(Q, num3);
	enqueue(Q, somma); 
	enqueue(Q, num);
	
}
