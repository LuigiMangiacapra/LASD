/*Scrivere una funzione che, data una coda Q di interi con cardinalità pari, modifichi Q in modo che sostituisca ad ogni coppia di valori
consecutivi, la loro somma. La funzione restituisce la coda modificata*/

#include <stdio.h>

#define MAX 20

int empty_queue(int Q[]){
	return Q[0] == 0;
}

int full_queue(int Q[]){
	return Q[MAX + 1] == 1;
}


void riempi_coda(int n_elem, int Q[]);
void enqueue(int Q[], int val);
int dequeue(int Q[]);
void print_queue(int Q[]);
void inizializza_queue(int Q[]);
void somma_cons(int Q[]);

int main(){
	int Q[MAX + 2];
	int n_elem;
	printf("Quanti elementi vuoi inserire?\n");
	scanf("%d", &n_elem);
	inizializza_queue(Q);//IMPORTANTE!
	riempi_coda(n_elem, Q);
	print_queue(Q);
	printf("\n");
	somma_cons(Q);
	print_queue(Q);
}

void inizializza_queue(int Q[]){
	Q[0]=0;
	Q[MAX+1]=1;
}	

void enqueue(int Q[], int val){
	Q[Q[MAX+1]] = val;
	if(Q[0] == 0)
		Q[0] = 1;
	Q[MAX + 1] = (Q[MAX + 1] % MAX) + 1;
}


int dequeue(int Q[]){
	int val = Q[Q[0]];
	Q[0] = (Q[0] % MAX) + 1;
	
	if(Q[0] == Q[MAX + 1]){
		Q[0] = 0;
		Q[MAX + 1] = 1;
	}
	return val;
}


void riempi_coda(int n_elem, int Q[]){
	int elem;
	if(n_elem != 0){
		printf("inserire un elemento:\n");
		scanf("%d", &elem);
		enqueue(Q, elem);
		n_elem = n_elem - 1;
		riempi_coda(n_elem, Q);	
	}
}

void print_queue(int Q[]){
	int val;
	if(!empty_queue(Q)){
		val = dequeue(Q);	
		printf("|%d| ", val);
		print_queue(Q);
		enqueue(Q, val);
	}
}

void somma_cons(int Q[]){
	int val, val2, somma = 0;
	
	if(!empty_queue(Q)){
		val = dequeue(Q);	
		val2 = dequeue(Q);
		somma = val + val2;
		somma_cons(Q);
		enqueue(Q, somma);
	}
}
