/*
Creare una coda e sostituire ogni elemento in posizione dispari 
con il doppio dell'elemento che lo precede

esempio: 1-2-3-4-5		1-2-4-4-8
*/

#include <stdio.h>

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
void substitute_odd_with_double(int Q[], int pos);

int main(){
	int num_elementi, pos = 0;
	int Q[MAX+1];
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
	substitute_odd_with_double(Q, pos);
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

void substitute_odd_with_double(int Q[], int pos){
	
	int val, doppio;
	
	if(!empty_queue(Q)){
		val = dequeue(Q);
		pos = pos - 1;//poiché si decoda dalla fine, la posizione deve essere decrementata dall'ultima posizione + 1 (esempio: 5 + 1)
		
		substitute_odd_with_double(Q, pos);
		
		//se la posizione è dispari e l'elemento precedente non è il 0-esimo (perché contiene l'indice di encodamento)
		if(pos % 2 != 0 && pos - 1 != 0){
			doppio = 2 * Q[pos - 1];//calcola il doppio dell'elemento precedente all'elemento in posizione dispari
			enqueue(Q, doppio);//inserisce l'elemento doppio nella posizione dispari calcolata durante la discesa
		}
		else
			enqueue(Q, val);//inserisce gli elementi in posizione pari senza modificarli
	}	
}

