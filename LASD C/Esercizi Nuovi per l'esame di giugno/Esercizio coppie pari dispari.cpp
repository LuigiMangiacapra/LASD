//Esercizio coppia pari, dispari


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
void elimina_coppie_pari_dispari(int Q[]);

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
	printf("Stampa dopo la funzione:\n");
	elimina_coppie_pari_dispari(Q);
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


void elimina_coppie_pari_dispari(int Q[]) {
	int val1 = 0, val2 = 0;
    if (!empty_queue(Q)) {
        val1 = dequeue(Q); // Primo elemento della coppia
        val2 = dequeue(Q); // Secondo elemento della coppia
        
        elimina_coppie_pari_dispari(Q); // Chiamata ricorsiva per elaborare le coppie successive
        
        enqueue(Q, val2);
        enqueue(Q, val1);
        
            
        
    }
}





