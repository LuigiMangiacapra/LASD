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

void new_queue(int Q[]);
void stampa_queue(int Q[]);
void rewerse (int Q[]);
void enqueue(int Q[], int valore);
int dequeue(int Q[]);
int togli_dispari( int Q[]);

main()
{
	int Q[MAX+2],scelta,valore; /* usare typedef per avere il main indipendente dalla scelta int Q[MAX+1] */
	do 
	{
		printf("\nscelta: 0-Crea, 1-Stampa, 2-Deq, 3-Enq, 4-togli dispari, 5-rewerse , 6-uscita :\n"); 
		scanf("%d",&scelta); 
		switch (scelta) 
		{
			case 0: 
				new_queue(Q); break;
			case 1: 
				stampa_queue(Q); break;
			case 2: 
				if (!empty_queue(Q)) 
					printf("\n Head della coda %d" , dequeue(Q)); 
				else 
					printf("\n spiacente, coda vuoto");
				break;
			case 3: 
				if (!full_queue(Q)) {
					printf("\n Valore da inserire nello stack: ");
					scanf("%d",&valore);
					enqueue(Q,valore); 
				}	 
				else 
					printf("\n spiacente, coda piena");
				break;
			case 4:
				togli_dispari(Q);
				rewerse(Q);//Serve perché quando riinseriamo i numeri pari, li riinseriamo in rewerse, durante la risalita della funzione ricorsiva
				stampa_queue(Q);
				break;
			case 5:
				rewerse(Q);
				stampa_queue(Q); 
		} /* fine switch */

	}
	while(scelta==0||scelta==1 ||scelta==2||scelta==3||scelta==4||scelta==5);
	} /* fine main() */
	
	
void inizializza_queue(int Q[]){
	Q[0]=0;//la prima posizione contiene la posizione in cui è presente il primo elemento(se è 0 allora l'array è vuoto)
	Q[MAX+1]=1;//l'ultima posizione dell'array contiene l'indice in cui è possibile inserire un elemento in coda(se è 1 allora l'array è vuoto)
}	
	
	
void new_queue(int Q[])
{ 
	int num_elementi,valore;
	inizializza_queue(Q); /* set s[0]=0 e s[MAX+1]=1 */
	printf("\n Quanti elementi (max %d elementi): ", MAX);
	scanf("%d",&num_elementi);
	while (num_elementi > MAX) {
		printf("\n max %d elementi: ", MAX);
		scanf("%d",&num_elementi);
	}
	while(num_elementi) {//cicla finché num_elementi è diverso da 0
		printf("\n Inserire un valore: ");
		scanf("%d",&valore);
		enqueue(Q, valore);//inserisce l'elemento in coda all'array
		num_elementi--;
	}
}


void stampa_queue(int Q[]) 
{ 
	int val;
	if (!empty_queue(Q)) 
	{
		val=dequeue(Q);//svuota la coda un elemento alla volta
		printf("[%d] ",val);//stampa gli elementi eliminati momentaneamente dalla coda
		stampa_queue(Q);//chiamata ricorsiva
		enqueue(Q,val); //riinserisce gli elementi precedentemente eliminati
	}
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


void enqueue(int Q[], int valore)
{
	Q[Q[MAX+1]] = valore;//inserisce l'elemento nella posizione indicata dall'ultima posizione dell'array
	if (Q[0] == 0) //se la coda è vuota aggiorna l'indice in testa in quanto precedentemente si è inserito un elemento in coda
		Q[0]=1;    //infatti si aggiorna ad 1
	Q[MAX+1] = (Q[MAX+1] % MAX) + 1; //aggiorna anche l'ultima posizione dell'array 
									 //non viene sommato direttamente 1 perché altrimenti sforerebbe il numero di elementi da inserire
}									 //infatti Q[MAX+1] % MAX se Q[MAX+1] < o > MAX restituirà Q[MAX+1] altrimenti 0, infatti se Q[MAX+1]=MAX, Q[MAX+1]%MAX=0.
							

int dequeue(int Q[]) 
{
	int valore=Q[Q[0]];//assegna a "valore" l'elemento che si trova in testa alla coda, indicato dal valore della prima posizone dell'array
	Q[0] = (Q[0] % MAX) + 1;//per non sforare con gli indici si esegue lo stesso procedimento attuato in enqueue per l'ultima posizione dell'array
	//Q[0] == Q[MAX+1] quando è piena o quando l'ultimo elemento rimosso è in coda
	if (Q[0] == Q[MAX+1]) {//questo if controlla se dopo il decodamento la lista è diventata vuota, se così fosse reimposta i valori dei due indici di posizione
		Q[0]=0; 
		Q[MAX+1]=1; 
	}
	return valore;
}

int togli_dispari(int Q[]){
	int elem;
	
	//CASO BASE
	//Se la lista è vuota risale la ricorsione
	if(!empty_queue(Q)){
		//Decoda tutti gli elementi
		elem=dequeue(Q);
		togli_dispari(Q);
		
		//Aggiunge in risalita gli elementi pari
		if(elem%2==0)
			enqueue(Q, elem);
	
	}
	
	
	return elem;
}
	



