/*
- Creare una coda e eliminare tutti gli elementi che hanno come precedente 
  e successivo numeri pari
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
void substitute_multiple_of_three(int Q[], int pos);
void elimina_tra_pari(int Q[], int pos, int num_values);

int main(){
	int num_elementi, pos = 0;
	int Q[MAX+1];
	srand(time(0));
	inizializza_queue(Q); /* set s[0]=0 e s[MAX+1]=1 */
				
	printf("\n Quanti elementi (max %d elementi): ", MAX);
	scanf("%d",&num_elementi);
				
	while (num_elementi > MAX) {
		printf("\n max %d elementi: ", MAX);
		scanf("%d",&num_elementi);
	}
	new_queue(Q, num_elementi); 
	stampa_queue(Q);
	printf("\n");
	
	pos = num_elementi + 1;
	elimina_tra_pari(Q, pos, num_elementi);
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



void elimina_tra_pari(int Q[], int pos, int num_values){
	int val;
	if(!empty_queue(Q)){
		
		pos = pos - 1;
		val = dequeue(Q);
		
		
		elimina_tra_pari(Q, pos, num_values); 
		printf("prec:%d, curr:%d, succ:%d, pos:%d\n", Q[pos-1], Q[pos], Q[pos+1], pos);
		if((Q[pos - 1] % 2 != 0 || Q[pos + 1] % 2 != 0) || pos == 1 || pos == num_values){
			
			enqueue(Q, val);
		}
	
			
	}
}
