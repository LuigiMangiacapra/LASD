#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int empty_stack(int S[])
{
return S[0]==0;
}

int full_stack(int S[])
{
return S[0]==MAX;
}

void push(int S[], int val);
int pop(int S[]);
void new_stack(int S[]);
void stampa_stack (int S[]);

main()
{
	int S[MAX+1],scelta,valore;
	do 
	{
		printf("\n\nscelta: 0-Crea, 1-Stampa, 2-Pop, 3-Push, 4-uscita:\n"); 
		scanf("%d",&scelta); 
		
		switch(scelta) 
		{
			case 0: 
				new_stack(S); break;
			case 1: 
				stampa_stack(S); break;
			case 2: 
				if (!empty_stack(S)) 
					printf("\n Top dello Stack %d" , pop(S)); 
				else 
					printf("\n spiacente, stack vuoto");
				break;
			case 3: 
				if (!full_stack(S)) {
					printf("\n valore da inserire nello stack: ");
					scanf("%d",&valore);
					push(S,valore); 
				}	 
				else 
					printf("\n spiacente, stack pieno");
		} /* fine switch */
	}
	while(scelta==0||scelta==1 ||scelta==2||scelta==3);
}
	
	
void push(int S[], int val){
	if (full_stack(S)) 
		return;
	else 
	{
		S[0] = S[0] + 1; //Primo valore incrementato quando viene inserito un nuovo elemento, esso indica dove è posizionato l'ultimo elemento dello stack
		S[S[0]]= val; //inserisce il valore nella nuova posizione vuota, successiva all'ultimo elemento, se presente.
	}
}	



int pop(int S[]){ 
	int val=0;
	if (empty_stack(S)) 
		return 0;
	else 
	{
		S[0] = S[0] - 1; //primo valore decrementato perché abbiamo intenzione di non considerare più quell'elemento, l'eliminazione avviene tramite la sovrascrittura e non eliminando realmente l'elemento
		val=S[S[0]+1];
	}
	return val;
}

void inizializza_stack(int S[]){
	S[0]=0; //Per inizializzare lo stack inseriamo come primo valore 0, perché inizialmente possiede 0 elementi
	
}

void new_stack(int S[]){
 
	int num_elementi,valore,err;
	inizializza_stack(S); 
	printf("\n Quanti elementi (max %d elementi): ", MAX);
	scanf("%d",&num_elementi);
	while (num_elementi > MAX) {
		printf("\n max %d elementi: ", MAX);
		scanf("%d",&num_elementi);
	}
	while(num_elementi != 0) {
		printf("\n Inserire un valore: ");
		scanf("%d", &valore);
		push(S, valore);
		--num_elementi;
	}
}


void stampa_stack (int S[]){
	
	int valore,err;
	if (!empty_stack(S)){
		
		valore= pop(S);
		printf(" %d ",valore);
		stampa_stack(S);
		push(S,valore);
	}
}



