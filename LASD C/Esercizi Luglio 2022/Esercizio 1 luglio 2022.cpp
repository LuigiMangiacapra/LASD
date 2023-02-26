/*
Scrivere una funzione che, data una coda Q di interi, modifichi Q in modo che sostituisca ad ogni
coppia di valori pari consecutivi, il doppio della loro somma.
La funzione restituisce la coda modificata

ESEMPIO: coda1: 2-4-6-7-6-8		output: 12-6-28
*/
#include <stdio.h>

#define MAX 20

int empty_queue(int Q[])
{
	return Q[0]==0;
}

int full_queue(int Q[]) 
{ 
	return Q[0]==Q[MAX+1];
}

void new_queue(int Q[], int num_elementi);
void stampa_queue(int Q[]);
void enqueue(int Q[], int valore);
int dequeue(int Q[]);
void inizializza_queue(int Q[]);
//void somma_doppi_pari(int Q[], int elem2, int count); 
void somma_doppi_pari(int Q[]);
void rewerse (int Q[]);

int main(){
	int num_elementi, Q[MAX+2];
	int count = 0, elem = 0;
	inizializza_queue(Q); /* set s[0]=0 e s[MAX+1]=1 */
				
	printf("\n Quanti elementi (max %d elementi): ", MAX);
	scanf("%d",&num_elementi);
				
	while (num_elementi > MAX) {
		printf("\n max %d elementi: ", MAX);
		scanf("%d",&num_elementi);
	}
	new_queue(Q, num_elementi);
	
	stampa_queue(Q); //quando si stampa una coda la si rewersa automaticamente a causa dell'encodamento nella risalita della ricorsione 
	rewerse(Q);
	//somma_doppi_pari(Q, elem, count); 
	somma_doppi_pari(Q);
	rewerse(Q);
	printf("\nCoda modificata\n");
	stampa_queue(Q);
	
}

void inizializza_queue(int Q[]){
	Q[0]=0;
	Q[MAX+1]=1;
}	
	
	
void new_queue(int Q[], int num_elementi)
{ 
	int valore;
	
	if(num_elementi != 0){
		printf("\n Inserire un valore: ");
		scanf("%d",&valore);
		enqueue(Q, valore);
		num_elementi--;
		new_queue(Q, num_elementi);
	}
}


void stampa_queue(int Q[]) 
{ 
	int val;
	if (!empty_queue(Q)) 
	{
		val=dequeue(Q);
		printf(" %d |",val);
		stampa_queue(Q);
		enqueue(Q,val); 
	}
}

void enqueue(int Q[], int valore)
{
	Q[Q[MAX+1]] = valore;
	if (Q[0] == 0) //Solo quando Q[0] == 0 va aggiornato ad 1 perché è il primo e unico elemento in testa se non si effettuano decodamenti
		Q[0]=1; 
	Q[MAX+1] = (Q[MAX+1] % MAX) + 1; // il % permette di andare oltre il limite dell'indice
}


int dequeue(int Q[]) 
{
	int valore=Q[Q[0]];
	Q[0] = (Q[0] % MAX) + 1;
	if (Q[0] == Q[MAX+1]) {//permette di aggiornate Q[0] a 0 quando la coda è stata completamente svuotata
		Q[0]=0; 
		Q[MAX+1]=1; 
	}
	return valore;
}


//funzione che inverte l'ordine degli elementi
void rewerse (int Q[]) 
{
	int val;
	if (!empty_queue(Q)) 
	{
		val=dequeue(Q);
		rewerse(Q);
		enqueue(Q,val); //enqueue inserisce gli elementi a salire identificando ogni locazione
						//come testa della coda
	}
}


/*void somma_doppi_pari(int Q[], int elem2, int count){
	int somma = 0, elem;
	
	if(!empty_queue(Q)){
		
		elem = dequeue(Q);
			
		//se l'elemento appena decodato è pari
		if(elem % 2 == 0){
			count = count + 1; //conta ogni elemento pari
			printf("\nelem: %d, count: %d\n", elem, count);
			
			if(count == 2){ //se si incontrano due elementi pari consecutivi		
				somma = 2 * (elem + elem2);	//crea la il doppio della somma dei due elementi apri consecutivi
				count = 0; //azzera il count perché l'operazione è stata effettuata
			}
		}
		else{
			if(count == 1){//serve per inserire un terzo elemento pari che non deve essere saltato
				somma = elem2;
			}
			count = 0;	
		}
		
		somma_doppi_pari(Q, elem, count);
		if(somma != 0)
			enqueue(Q, somma);
	}
}*/


void somma_doppi_pari(int Q[]){
	int val1, val2, somma;
	if(!empty_queue(Q)){
		val1 = dequeue(Q);
		val2 = dequeue(Q);
		
		somma_doppi_pari(Q);
		
		if(val1 % 2 == 0 && val2 % 2 == 0){
			somma = val1 + val2;
			enqueue(Q, 2 * somma);
		}
		else if(val1 % 2 == 0){
			enqueue(Q, val1);
		}
		else if(val2 %2 == 0){
			enqueue(Q, val2);
		}
			
	}
}
