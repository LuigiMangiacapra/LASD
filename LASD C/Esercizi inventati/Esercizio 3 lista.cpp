/*
  Creare una coda e eliminare tutti gli elementi che hanno come precedente 
  e successivo numeri pari
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

struct elem *crea_lista(int n);
void visualizza_lista(struct elem *lista);
struct elem* elimina_tra_pari(struct elem* lista, struct elem* elem, int pos, int act_pos);


struct elem{
	int inf;
	struct elem *next;
};


int main(){
	int pos = 0, act_pos = 0;
	struct elem* elem = NULL;
	struct elem *lista = NULL; //puntatore che si collega alla struct per creare la lista
	int n;
	printf("Specificare numero di elementi\n");
	scanf("%d", &n);
	lista=crea_lista(n);
	lista = elimina_tra_pari(lista, elem, pos, act_pos);
	visualizza_lista(lista);
}


struct elem *crea_lista(int n){
	struct elem *testa, *punt;
	int i;
	
	if(n==0){
		testa=NULL;
	}
	else{
		testa=(struct elem *)malloc(sizeof(struct elem));
		printf("inserire primo elemento\n");
		scanf("%d",&testa->inf);
		punt=testa;
		for(i=2;i<=n;i++){
			punt->next=(struct elem *)malloc(sizeof(struct elem));
			punt=punt->next;
			printf("inserire il %d elemento:\n",i);
			scanf("%d",&punt->inf);
		
		}
		punt->next=NULL;
	
	}
	return(testa);
}


void visualizza_lista(struct elem *p) {
	printf("\n lista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 


int is_prime(int n){
	int m, i = 0, flag = 0;
	m=n/2;    
	for(i=2;i<=m;i++){    
		if(n%i==0){      
			flag=1;    
			break;    
		}    
	}    
	if(flag==0)    
		return 1;    
	return 0;  
}


int find_somma(struct elem* lista, int somma){
	
	if(lista != NULL){
		
		somma = find_somma(lista->next, somma);
		if(is_prime(lista->inf)){
			somma = somma + lista->inf;
		}
	}
	return somma;
}


struct elem* elimina_tra_pari(struct elem* lista, struct elem* elem, int pos, int act_pos){
	struct elem* temp = NULL;
	struct elem* doub = NULL;
	if(lista != NULL){
		
		pos = pos + 1;
		
		if(lista->inf % 2 == 0){
			act_pos = pos;
		}
		
		lista->next = elimina_tra_pari(lista->next, elem, pos, act_pos);
		
		if(act_pos == pos){
			doub = lista;//conserva l'elemento pari iniziale
			if(lista->next->next != NULL && lista->next->next->inf % 2 == 0){
				lista = lista->next;//passa all'elemento da eliminare
				temp = lista;//conserva l'elemento eliminare in temp
				lista = lista->next;//cambia il puntatore dall'elemento da eliminare al successivo
				free(temp);//elimina l'elemento
				doub->next = lista;//l'elemento successivo del pari iniziale sarà il pari successivo
				lista = doub;//riassegna a lista il nodo iniziale per permettere alla
							 //risalita dalla ricorsione di funzionare correttamente e non saltare un elemento
			}
			
		}
		
	}
	return lista;
}
