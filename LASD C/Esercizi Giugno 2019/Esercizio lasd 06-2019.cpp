/*
Si consideri una Coda Q, implementato con array Q[MAX]. Si implementi la
funzione ricorsiva void togliPositiviNegativi(int Q[MAX]) che elimina dalla
coda, a seconda della scelta, i numeri positivi o negativi. L’ordine della coda
deve essere invariato
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 20

int empty_queue(int Q[]){

	return (Q[0]==0);
}

int full_queue(int Q[]){

	return (Q[0]==Q[MAX+2]);
}


//void new_queue(int Q[]);
void new_queue(int Q[],int n);
void stampa_queue(int Q[]);
void rewerse (int Q[]);
void enqueue(int Q[], int valore);
int dequeue(int Q[]);
void togliPositiviNegativi(int Q[],int val);
void inizializza_queue(int Q[]);


int main(){
	int Q[MAX+2], elemento, valore, num_elem, scelta, val;
		
	do{
		printf("\nSeleziona operazione da effettuare:\n");
		printf("1-Crea coda, 2-Stampa coda, 3-decoda, 4-encoda, 5-elimina positivi o negativi, 6-esci\n");
		scanf("%d",&scelta);
		switch(scelta){
			case 1:
				//new_queue(Q);
				printf("Quanti elementi vuoi inserire(max: %d)?\n",MAX);
				scanf("%d", &num_elem);
				
				while(num_elem>MAX){
					printf("Non puoi inserire più elementi di %d, RIPROVARE!\n",MAX);
					scanf("%d", &num_elem);
				}
				inizializza_queue(Q);
				new_queue(Q,num_elem);
			break;
			case 2:
				stampa_queue(Q);
				
			break;
			case 3:
				if(!empty_queue(Q)){
					printf("La testa della coda è: %d\n", dequeue(Q));
					
				}
				else{
					printf("Spiacente, la coda e' vuota\n");
				}
			case 4:
				if(!full_queue(Q)){
					printf("Inserire elemento da mettere in coda\n");
					scanf("%d",&elemento);
					enqueue(Q, elemento);
				}
				else{
					printf("Impossibile inserire l'elemento, la coda e' piena!\n");
				
				}
				break;
			case 5:
				printf("inserire 1 se vuoi eliminare positivi, 2 se vuoi eliminare negativi\n");
				scanf("%d",&val);
				togliPositiviNegativi(Q,val);
				
		}
		
	}
	while(scelta==1 || scelta==2 || scelta==3 || scelta==4 || scelta==5);
}


void togliPositiviNegativi(int Q[],int val){
		int elemento;
		if(!empty_queue(Q)){
			elemento=dequeue(Q);
			togliPositiviNegativi(Q,val);
		
			//inserisce gli elementi negativi
			if(elemento<0 && val==1)
				enqueue(Q,elemento);
			//inserisce gli elementi positivi
			if(elemento>0 && val==2)
				enqueue(Q,elemento);
			
		}
		rewerse(Q);
}


void inizializza_queue(int Q[]){
	Q[0]=0;
	Q[MAX+1]=1;
}


/*void new_queue(int Q[])
{ 
	int num_elementi,valore;
	inizializza_queue(Q);  set s[0]=0 e s[MAX+1]=1 
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
}*/

void new_queue(int Q[], int n){
	int elem;
	if(n!=0){
		printf("Inserisci elemento:\n");
		scanf("%d",&elem);
		enqueue(Q,elem);
		new_queue(Q, n-1);
	}
}


void stampa_queue(int Q[]){
	int val;
	if(!empty_queue(Q)){
		val=dequeue(Q);
		printf("|%d| ", val);
		stampa_queue(Q);
		enqueue(Q,val);
	}
	
}


void enqueue(int Q[],int valore){
	Q[Q[MAX+1]]=valore;
	//modifica primo e ultimo indice se la coda è vuoto
	if(Q[0]==0)
		Q[0]=1;
	Q[MAX+1]=(Q[MAX+1] % MAX)+1;
	
	

}


int dequeue(int Q[]){
	int valore = Q[Q[0]];
	Q[0] = (Q[0] % MAX)+1;
	if (Q[0] == Q[MAX+1]) {
		Q[0]=0; 
		Q[MAX+1]=1; 
	}
	return valore;
}


void rewerse (int Q[]){
	int val;
	if(!empty_queue){
		val=dequeue(Q);
		rewerse(Q);
		enqueue(Q,val);
	}
}
