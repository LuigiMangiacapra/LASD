#include <stdio.h>
#define MAX 20

int empty_queue(int Q[])
{
return Q[0]==0;
}

int full_queue( int Q[]) 
{ 
return Q[0]==Q[MAX+2];
}

void new_queue(int Q[]);
void stampa_queue(int Q[]);
void rewerse (int Q[]);
void enqueue(int Q[], int valore);
int dequeue(int Q[]);
void gioco(int Q1[], int Q2[]);

main()
{
	int Q[MAX+2],scelta,valore; /* usare typedef per avere il main indipendente dalla scelta int Q[MAX+1] */
	do 
	{
		printf("\n scelta: 0-Crea, 1-Stampa, 2-Deq, 3-Enq, 4-gioco, 5-uscita:\n"); 
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
				break;
			case 4:
				int Q1[MAX+2], Q2[MAX+2];
				new_queue(Q1);
				new_queue(Q2);
				gioco(Q1, Q2);
				
				if(empty_queue(Q1)){
					printf("La seconda coda ha vinto il gioco\n");
				}
				if(empty_queue(Q2)){
					printf("La prima coda ha vinto il gioco\n");
				}
		} /* fine switch */

	}
	while(scelta==0||scelta==1||scelta==2||scelta==3||scelta==4);
	} /* fine main() */
	
	
void inizializza_queue(int Q[]){
	Q[0]=0;
	Q[MAX+1]=1;
}	
	
	
void new_queue(int Q[])
{ 
	int num_elementi,valore;
	inizializza_queue(Q); /* set s[0]=0 e s[MAX+1]=1 */
	printf("\n Quanti elementi (max %d elementi): ", MAX);
	scanf("%d",&num_elementi);
	while (num_elementi >MAX) {
		printf("\n max %d elementi: ", MAX);
		scanf("%d",&num_elementi);
	}
	while(num_elementi) {
		printf("\n Inserire un valore: ");
		scanf("%d",&valore);
		enqueue(Q, valore);
		num_elementi--;
	}
}


void stampa_queue(int Q[]) 
{ 
	int val;
	if (!empty_queue(Q)) 
	{
		val=dequeue(Q);
		printf("[%d] ",val);
		stampa_queue(Q);
		enqueue(Q,val); 
	}
}


void enqueue(int Q[], int valore)
{
	Q[Q[MAX+1]] = valore;
	if (Q[0] == 0) 
		Q[0]=1; 
	Q[MAX+1] = (Q[MAX+1] % MAX) + 1; 
}


int dequeue(int Q[]) 
{
	int valore=Q[Q[0]];
	Q[0] = (Q[0] % MAX) + 1;
	if (Q[0] == Q[MAX+1]) {
		Q[0]=0; 
		Q[MAX+1]=1; 
	}
	return valore;
}

void gioco(int Q1[], int Q2[]){
	int valore1, valore2;
	//Somma di due elementi
	int sum = Q1[Q1[0]] + Q2[Q2[0]];
	printf("Primo elemento di Q1: %d\n", Q1[Q1[0]]);
	printf("posizione testa1: %d\n", Q1[0]);
	
	printf("Primo elemento di Q2: %d\n", Q2[Q2[0]]);
	printf("posizione testa2: %d\n", Q2[0]);
	printf("sum: %d\n", sum);
	
	//Se le due code non sono vuote effettua l'operazione
	if(!empty_queue(Q1) && !empty_queue(Q2)){
		//se la somma%10 < 5 decoda da Q2 perché ha perso il turno altrimenti da Q1
		if(sum%10<5){
			printf("Q1 ha vinto il turno\n");
			valore1=dequeue(Q2);
			printf("elemento eliminato da Q2: %d\n", valore1);
		}
		else{
			printf("Q2 ha vinto il turno\n");
			valore2=dequeue(Q1);
			printf("elemento eliminato da Q1: %d\n", valore2);
		}
	
		gioco(Q1,Q2);
	}
	
	//Se Q1 è vuota ricostruisce Q2 (la coda vincente)
	if(empty_queue(Q1)){
		enqueue(Q2,valore1);
	}	
	//Se Q2 è vuota ricostruisce Q1 (la coda vincente)
	else if(empty_queue(Q2)){
		enqueue(Q1,valore2);
	} 
	
	
	
	
}
