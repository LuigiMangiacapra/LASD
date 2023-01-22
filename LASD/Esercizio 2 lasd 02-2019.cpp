/*
Date due liste implementa la funzione di togli negativi che elimina da L1
tutti i negativi e i poisitivi da L2 senza cambiare ordine. Implementare la
funzione interleaving che date due liste restituisce il loro interleaving tale
che mette un elemento di L1 ogni due di L2 fino a che una delle due non si
annulla.
*/

#include <stdio.h>
#include <malloc.h>
#define MAX 20

struct elem{
	int inf;
	struct elem* next;

};

struct elem* crea_lista(struct elem* lista);
void visualizza_lista(struct elem* lista);
struct elem* modifica_liste(struct elem* L1);
struct elem* modifica_liste2(struct elem* L2);
void togli_negativi(struct elem* L1, struct elem* L2);
struct elem* interleaving(struct elem* L1, struct elem* L2, int i);
int size(struct elem *L);

int main(){
	struct elem* lista1, *lista2;
	int i=1;
	lista1=crea_lista(lista1);
	lista2=crea_lista(lista2);
	visualizza_lista(lista1);
	visualizza_lista(lista2);
	//togli_negativi(lista1, lista2);
	lista2=interleaving(lista1, lista2, i);
	visualizza_lista(lista2);
}


struct elem* crea_lista(struct elem* lista){
	struct elem* punt;
	int elem,ins;
	printf("Specificare numero di elementi(max %d):\n",MAX);
	scanf("%d",&elem);
	
	if(elem==0){
		lista=NULL;
	}
	else{
		lista=(struct elem*)malloc(sizeof(struct elem*));
		printf("Specificare il primo elemento:\n");
		scanf("%d",&lista->inf);
		punt=lista;
		for(int i=2; i<=elem; i++){
			punt->next=(struct elem*)malloc(sizeof(struct elem*));
			punt=punt->next;
			printf("Specificare elemento da inserire:\n");
			scanf("%d",&punt->inf);
		}
		punt->next=NULL;
		
	}	
	return lista;
}
	

void visualizza_lista(struct elem* lista){
	
	if(lista != NULL){
		printf("%d",lista->inf);
		printf(" ---> ");
		visualizza_lista(lista->next);
	
	}
	
	if(lista==NULL)
		printf("NULL\n\n");

}



struct elem* modifica_liste2(struct elem* L2){
	struct elem* tmp; 
	if(L2!=NULL){
		L2->next=modifica_liste2(L2->next);
		if(L2->inf>0){
			tmp=L2;
			L2=L2->next;
			free(tmp);
		}
	}
	
	
	return L2;
}



struct elem* modifica_liste(struct elem* L1){
	struct elem* tmp; 
	if(L1!=NULL){
		L1->next=modifica_liste(L1->next);
		if(L1->inf<0){
			tmp=L1;
			L1=L1->next;
			free(tmp);
		}
	}
	
	return L1;
}


void togli_negativi(struct elem* L1, struct elem* L2){
	L1 = modifica_liste(L1);
	L2 = modifica_liste2(L2);
	visualizza_lista(L1);
	visualizza_lista(L2);
}


//funzione simile al merge solo che inserisce ogni elemento di L1 ogni 2 di L2

//mette un elemento di L1 ogni due di L2 fino a che una delle due non si annulla
struct elem* interleaving(struct elem* L1, struct elem* L2, int i){
	
	//CASO BASE
	if(L1->next==NULL || L2->next==NULL || L2->next->next==NULL){
		if(size(L1)>size(L2) && L2->next==NULL){
			L2->next=L1->next;
			L1->next=NULL;
			return L2;
		}
		else if(size(L1)>size(L2) && L2->next->next==NULL){
			L2->next->next=L1->next;
			L1->next=NULL;
			return L2;
		}		
		else{
			L1->next=L2->next;
			L1->next=NULL;
			return L1;
		}
	}
	printf("%d\n", i);
	//CASO INDUTTIVO
	if(i%2!=0){
		L2->next->next=interleaving(L1, L2->next->next, i++);
		
		return L2;
	}
	if(i%2==0){
		L1->next=interleaving(L1->next, L2, i++);
	
		return L1;
	}
	
	
}


int size(struct elem *L){
	int dim=0;
	if(L!=NULL){
		dim+=1;
		dim=size(L->next);
	}
	return dim;
}
