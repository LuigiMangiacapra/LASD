/*
Date due liste doppiamente concatenate,l1 ed l2, fare le seguenti cose:
a) eliminare da l1 i negativi ed inserirli in testa ad l2
b) eliminare da l2 i positivi ed inserirli in testa ad l1
c) restituire le due liste così modificate.
*/

#include <stdio.h>
#include <malloc.h>
#define MAX 20

typedef struct elem{
	int inf;
	struct elem *next;
	struct elem *prev;

}nodo;


nodo* crea_lista();
nodo* inserisci_testa(nodo* L, int valore);
void visualizza_lista(nodo* L);
nodo* modifica_liste(nodo* L1, nodo* L2);
nodo* modifica_liste2(nodo* L1, nodo* L2);



int main(){
	nodo *L1, *L2;
	L1=crea_lista();
	L2=crea_lista();
	visualizza_lista(L1);
	visualizza_lista(L2);
	L1=modifica_liste(L1, L2);
	L2=modifica_liste2(L1, L2);
	visualizza_lista(L1);
	visualizza_lista(L2);
}


nodo* crea_lista(){
	nodo* L, *punt;
	int n_val,elem;
	
	printf("Quanti elementi vuoi inserire(max %d)\n",MAX);
	scanf("%d",&n_val);
	
	if(n_val==0){//gestire prima l'inserimento di 0 valori
		L==NULL;
	}
	else{
		L=(nodo*)malloc(sizeof(nodo*));
		printf("Inserire elemento:\n");
		scanf("%d",&L->inf);
		punt=L;//utilizzare un altro puntatore che servirà per scorrere la lista
		L->prev=NULL;
		
		//inizia a scorrere il resto della lista per inserire altri elementi
		for(int i=2; i<=n_val; i++){
			punt->next=(nodo*)malloc(sizeof(nodo*));//poiché punt, punta L creiamo la malloc su punt->next
			punt->next->prev=punt;//IMPORTANTE! associa all'elemento successivo il precedente, cioè il precedente del successivo è 
			punt = punt->next;//perché punt punta ancora all'elemento testa creto precedentemente
			printf("Inserire elemento:\n");
			scanf("%d",&punt->inf);	
				
		}
		punt->next=NULL;
		
	}
	return L;
}


void visualizza_lista(nodo* L){
	
	if(L!=NULL){
		printf("%d",L->inf);
		printf("---->");
		visualizza_lista(L->next);
	}
	if(L==NULL)
		printf("NULL\n");
}


nodo* inserisci_testa(nodo* L, int valore){
	nodo* temp;

	temp = (nodo*)malloc(sizeof(nodo*));
	temp->inf=valore;
	temp->prev=NULL;
	temp->next=L;
	L->prev=temp;
	L=temp;
	
	return L;
}



nodo* modifica_liste2(nodo* L1, nodo* L2){
	nodo* tmp; 
	if(L2!=NULL){
		L2->next=modifica_liste2(L1, L2->next);
		if(L2->inf>0){
			//inserisce l'elemento di L2 in testa a L1
			L1=inserisci_testa(L1, L2->inf);
			//elimina l'elemento di L2 inserito precedentemente in L1
			tmp=L2;
			L2=L2->next;
			free(tmp);
		}
	}
	
	
	return L2;
}



nodo* modifica_liste(nodo* L1, nodo* L2){
	nodo* tmp; 
	if(L1!=NULL){
		L1->next=modifica_liste(L1->next, L2);
		if(L1->inf<0){
			L2=inserisci_testa(L2, L1->inf);
			tmp=L1;
			L1=L1->next;
			free(tmp);
		}
	}
	
	return L1;
}






