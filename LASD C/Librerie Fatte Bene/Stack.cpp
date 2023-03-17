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

void push(int S[], int val, int *err);
int pop(int S[],int *err);
void new_stack(int S[]);
void stampa_stack (int S[]);

main()
{
	int S[MAX+1],scelta,valore,err;
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
					printf("\n Top dello Stack %d" , pop(S,&err)); 
				else 
					printf("\n spiacente, stack vuoto");
				break;
			case 3: 
				if (!full_stack(S)) {
					printf("\n valore da inserire nello stack: ");
					scanf("%d",&valore);
					push(S,valore,&err); 
				}	 
				else 
					printf("\n spiacente, stack pieno");
		} /* fine switch */
	}
	while(scelta==0||scelta==1 ||scelta==2||scelta==3);
}
	
	
void push(int S[], int val, int *err)
{
	if (full_stack(S)) 
		*err=1;
	else 
	{
		S[0] = S[0] + 1; //Primo valore incrementato quando viene inserito un nuovo elemento, esso indica dove � posizionato l'ultimo elemento dello stack
		S[S[0]]= val; //inserisce il valore nella nuova posizione vuota, successiva all'ultimo elemento, se presente.
		*err=0;
	}
}	



int pop(int S[],int *err)
{ 
	int val=0;
	if (empty_stack(S)) 
		*err=1;
	else 
	{
		S[0] = S[0] - 1; //primo valore decrementato perch� abbiamo intenzione di non considerare pi� quell'elemento, l'eliminazione avviene tramite la sovrascrittura e non eliminando realmente l'elemento
		val=S[S[0]+1];
		*err=0;
	}
	return val;
}

void inizializza_stack(int S[])
{
	S[0]=0; //Per inizializzare lo stack inseriamo come primo valore 0, perch� inizialmente possiede 0 elementi
	
}

void new_stack(int S[])
{ 
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
		push(S, valore,&err);
		--num_elementi;
	}
}


void stampa_stack ( int S[])
{
	int valore,err;
	if (!empty_stack(S))
	{
		valore= pop(S,&err);
		printf(" %d ",valore);
		stampa_stack(S);
		push(S,valore,&err);
	}
}



