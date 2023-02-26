/*
	Sostituire ogni elemento della coda con la media della somma del valore a sinistra e a destra solo se ne ha entrambi
	es° Input: 2-7-3-1-9	Output: 2-2-4-6-9
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

void inserisci_in_coda(int Q[], int n_elem);
void enqueue(int Q[], int val);
int dequeue(int Q[]);
void print(int Q[]);
void inizializza_coda(int Q[]);
void replaceWithAverage(int arr[], int size, int index);
void rewerse(int Q[]);

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
	replaceWithAverage(Q, n_elem, count);

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


//Sostituisce ogni valore con la media dei valori limitrofi
void replaceWithAverage(int arr[], int size, int index) {
	int left, right, avg;
    if (index == size + 1) {
        return; // Arrivati all'ultimo elemento, non fare nulla
    }
    
    if((index == 0 || index == (size + 1)) || ((index - 1) == 0 || (index + 1) == (size + 1))){
    	avg = arr[index];
	}
    else{
    	left = arr[index-1];
	    right = arr[index+1];
	    avg = (left + right) / 2;
	    printf("index: %d, left: %d, right: %d, avg: %d\n",index, left, right, avg);
	}
    
    dequeue(arr); // Rimuove l'elemento corrente dalla coda
    enqueue(arr, avg); // Inserisce la media calcolata nella coda
    
    replaceWithAverage(arr, size, index+1); // Chiama la funzione ricorsiva sul successivo elemento
    
    
}


void rewerse(int Q[]){
	int val;
	if(Q[0] != 0){
		val=dequeue(Q);
		rewerse(Q);
		enqueue(Q,val); 
		
	}
	
}

