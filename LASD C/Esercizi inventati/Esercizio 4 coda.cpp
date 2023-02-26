/*
Creare una coda e inserire elementi in coda con il valore della somma 
dei valori in posizione pari e valore dispari
	esempio:
		input: 2, 5, 7, 3, 2
		output: 2, 5, 7, 3, 2, 8
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int empty_queue(int Q[]){
	return Q[0] == 0;
}

int full_queue( int Q[]) 
{ 
	return Q[0]==Q[MAX+1];
}

void new_queue(int Q[], int num_elementi);
void stampa_queue(int Q[]);
void rewerse (int Q[]);
void enqueue(int Q[], int valore);
int dequeue(int Q[]);
void inizializza_queue(int Q[]);
void aggiungi_somma_dispari_in_pari(int Q[], int pos, int somma, int num_values);

int main(){
	int num_elementi = 0, somma = 0, pos = 0;
	int Q[MAX+1];
	srand(time(0));
	inizializza_queue(Q); /* set s[0]=0 e s[MAX+1]=1 */
				
	printf("\n Quanti elementi (max %d elementi): ", MAX);
	scanf("%d", &num_elementi);
				
	while (num_elementi > MAX) {
		printf("\n max %d elementi: ", MAX);
		scanf("%d",&num_elementi);
	}
	new_queue(Q, num_elementi); 
	stampa_queue(Q);
	printf("\n");
	
	rewerse(Q);
	aggiungi_somma_dispari_in_pari(Q, pos, somma, 5);
	rewerse(Q);
	stampa_queue(Q);
	
 
}

void inizializza_queue(int Q[]){
	Q[0] = 0;
	Q[MAX+1] = 1;
}


void new_queue(int Q[], int num_elementi){
	int valore;
	if(num_elementi){
		printf("\n Inserire un valore: ");
		scanf("%d",&valore);
		enqueue(Q, valore);
		num_elementi--;
		new_queue(Q, num_elementi);
	}
	
}


void stampa_queue(int Q[]){
	int val;
	if(!empty_queue(Q)){
		val = dequeue(Q);
		printf(" %d |",val);
		stampa_queue(Q);
		enqueue(Q, val);
	}
	
}


int dequeue(int Q[]){
	int valore = Q[Q[0]];
	Q[0] = (Q[0] % MAX) + 1;
	//se la coda è stata appena svuotata, impostare l'indice a 0
	if(Q[0] == Q[MAX+1]){
		Q[0] = 0;
		Q[MAX+1] = 1;
	}
	
	return valore;
}

void enqueue(int Q[], int valore){
	Q[Q[MAX+1]] = valore;
	
	if(Q[0] == 0){//Se si aggiunge un elemento in coda e Q[0] == 0 verrà aggiornato ad 1
				  //Perché Q[0] == 0 solo quando la coda è vuota, appena si inserisce un elemento
				  //L'elemento in testa sarà ovviamente Q[1]
		Q[0]=1; 
	}
	//Aggiorna l'indice della coda
	Q[MAX+1] = (Q[MAX+1] % MAX) + 1;
	
}


void rewerse(int Q[]){
	int val;
	if(!empty_queue(Q)){
		val = dequeue(Q);
		rewerse(Q);
		enqueue(Q, val);
	}
}



void aggiungi_somma_dispari_in_pari(int Q[], int pos, int somma, int num_values){
	int val;
	if(!empty_queue(Q)){
		val = dequeue(Q);
		if(pos < num_values)
			pos = pos + 1;
			
		printf("pos:%d, val:%d, num_values:%d\n", pos, val, num_values);
		if(pos % 2 == 0 && val % 2 != 0){
			somma = somma + val;
		}
		aggiungi_somma_dispari_in_pari(Q, pos, somma, num_values);
		
		if(pos == num_values)
			enqueue(Q, somma);
		else
			enqueue(Q, val);
		
	}
	
}
