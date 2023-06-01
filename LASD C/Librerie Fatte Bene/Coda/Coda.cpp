#include <stdio.h>
#define MAX 20

int empty_queue(int Q[])
{
	return Q[0]==0;
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

main()
{
	int Q[MAX+2],scelta,valore; /* usare typedef per avere il main indipendente dalla scelta int Q[MAX+1] */
	do 
	{
		printf("\n scelta: 0-Crea, 1-Stampa, 2-Deq, 3-Enq,, 4-uscita :\n"); 
		scanf("%d",&scelta); 
		switch (scelta) 
		{
			case 0: 
				int num_elementi;
				inizializza_queue(Q); /* set s[0]=0 e s[MAX+1]=1 */
				
				printf("\n Quanti elementi (max %d elementi): ", MAX);
				scanf("%d",&num_elementi);
				
				while (num_elementi > MAX) {
					printf("\n max %d elementi: ", MAX);
					scanf("%d",&num_elementi);
				}
				new_queue(Q, num_elementi); 
				break;
			case 1: 
				stampa_queue(Q); 
				break;
			case 2: 
				if (!empty_queue(Q)) 
					printf("\n Head della coda %d" , dequeue(Q)); 
				else 
					printf("\n spiacente, coda vuota");
				break;
			case 3: 
				if (!full_queue(Q)) {
					printf("\n Valore da inserire nello stack: ");
					scanf("%d",&valore);
					enqueue(Q,valore); 
				}	 
				else 
					printf("\n spiacente, coda piena");
		} /* fine switch */

	}
	while(scelta==0||scelta==1 ||scelta==2||scelta==3);
} /* fine main() */
	
	
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
	if (!empty_queue(Q)) //la cda è vuota quando Q[0] == 0 e lo si usa come condizione del caso base di una funzione ricorsiva affinché si fermi
	{
		val=dequeue(Q);
		printf(" %d |",val);
		stampa_queue(Q);
		enqueue(Q,val); 
	}
}

void rewerse(int Q[]){
	int val;
	if(!empty_queue(Q)){
		val=dequeue(Q);
		rewerse(Q);
		enqueue(Q,val); 
		
	}
	
}


void enqueue(int Q[], int valore)
{
	Q[Q[MAX+1]] = valore; //inserimento del valore nella posizione indicata da MAX + 1
	if (Q[0] == 0) //Solo quando Q[0] == 0, cioè quando la coda è vuota, va aggiornato ad 1 perché è il primo e unico elemento in testa se non si effettuano decodamenti
		Q[0]=1; 
	Q[MAX+1] = (Q[MAX+1] % MAX) + 1; // il % permette di andare oltre il limite dell'indice senza andare in overflow
}


int dequeue(int Q[]) 
{
	int valore = Q[Q[0]];
	Q[0] = (Q[0] % MAX) + 1;
	if (Q[0] == Q[MAX+1]) {//permette di aggiornate Q[0] a 0 quando la coda è stata completamente riempita o completamente svuotata in cui i due indici coincidono
							//se i due indici coincidono vuol dire che la coda è completamente vuota o completamente piena perché ciclicamente il dequeue e l'enqueue
							//agiscono sugli indici e bisogna reinizializzare il primo indice a 0 e l'ultimo a 1 perché si annullano a vicenda
		Q[0] = 0; 
		Q[MAX+1] = 1; 
	}
	return valore;
}

