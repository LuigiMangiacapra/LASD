/*
	
	creare una coda e sostituire tutti gli elementi in posizione pari con la media della somma di tutti gli elementi in posizione dispari
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

void inserisci_in_coda(int Q[], int n_elem);
void enqueue(int Q[], int val);
int dequeue(int Q[]);
void print(int Q[]);
void inizializza_coda(int Q[]);
void rewerse(int Q[]);
int OddPosAvg(int Q[], int somma, int size);
void replaceEvenPosWithOddPosAvg(int Q[], int pos, int avg);
void funzioneFinale(int Q[]);


int main(){
	
	int n_elem;
	int Q[MAX + 2];
	int count = 1;
	printf("Inserire la lunghezza della coda\n");
	scanf("%d", &n_elem);
	
	while(n_elem > MAX){
		printf("Inserire max %d elementi\n", MAX);
		scanf("%d", &n_elem);	
	}
	
	inizializza_coda(Q);
	inserisci_in_coda(Q, n_elem);
	print(Q);
	printf("\n");
	rewerse(Q);
	funzioneFinale(Q);

	print(Q);
}

void inizializza_coda(int Q[]){
	Q[0] = 0;
	Q[MAX + 1] = 1;
}


void inserisci_in_coda(int Q[], int n_elem){
	int val;
	//se la coda non è vuota
	if(n_elem != 0){
		printf("Inserire elemento nella coda\n");
		scanf("%d", &val);
		enqueue(Q, val);
		n_elem = n_elem - 1;
		inserisci_in_coda(Q, n_elem);
	}
	
}



void enqueue(int Q[], int val){
	Q[Q[MAX + 1]] = val;
	
	if(Q[0] == 0){
		Q[0] = 1;
	}
	
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


void print(int Q[]){
	int val;
	
	if(Q[0] != 0){
		val = dequeue(Q);
		printf("|%d| ", val);
		print(Q);
		enqueue(Q, val);
	}
	
}

int OddPosAvg(int Q[], int somma, int size){
	int val;
	if(Q[0] != 0){
		val=dequeue(Q);
		if(size % 2 != 0){
			somma = somma + val;
			size = size + 1;
		}
		
		enqueue(Q,val);
		return OddPosAvg(Q, somma, size);
	}
	else{
		return somma/ (size / 2);
	}
}


//sostituisce tutti gli elementi in posizione pari con la media della somma di tutti gli elementi in posizione dispari
void replaceEvenPosWithOddPosAvg(int Q[], int pos, int avg) {
	int val;
	if(Q[0] != 0){
		
		val = dequeue(Q);
			
		if(pos % 2 == 0){
			val = avg;
		}	
		replaceEvenPosWithOddPosAvg(Q, pos+1, avg);
		
		enqueue(Q, val);
	}
       
}


void funzioneFinale(int Q[]){
	int pos = 1, avg, somma = 0, size = 0;
	avg = OddPosAvg(Q, somma, size);
	printf("%d\n", avg);
	replaceEvenPosWithOddPosAvg(Q, pos, avg);
}


void rewerse(int Q[]){
	int val;
	if(Q[0] != 0){
		val=dequeue(Q);
		rewerse(Q);
		enqueue(Q,val); 
		
	}
	
}

