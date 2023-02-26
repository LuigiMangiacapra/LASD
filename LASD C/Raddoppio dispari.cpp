/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L, raddoppi tutti gli elementi dispari 
della lista
*/



#include <stdio.h>
#include <malloc.h>

struct elem *crea_lista();
void visualizza_lista(struct elem *lista);
struct elem *raddoppia_dispari(struct elem *l);

struct elem{
	int inf;
	struct elem *next;
};

int main(){
	struct elem *lista; //puntatore che si collega alla struct per creare la lista
	lista=crea_lista();
	visualizza_lista(lista);
	lista=raddoppia_dispari(lista);
	visualizza_lista(lista);
}


struct elem *crea_lista(){
	struct elem *testa, *punt;
	int i, n;
	printf("Specificare numero di elementi\n");
	scanf("%d", &n);
	
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
			printf("inserire il %d° elemento:\n",i);
			scanf("%d",&punt->inf);
		
		}
		punt->next=NULL;
	
	}
	return(testa);
}



void visualizza_lista(struct elem *p) {
	printf("\nlista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 



struct elem *raddoppia_dispari(struct elem *l){
	struct elem *tmp=l;
	//CASO BASE (INVERTITO)
	if(l!=NULL){
		//La chiamata ricorsiva viene effettuata prima per agire dagli ultimi elementi della lista
		l->next=raddoppia_dispari(l->next);
		//appena l==null (comincia la risalita della ricorsione)
		//se l'elemento è dispari
		if(l->inf%2!=0){
			//crea una copia del nodo con elemento dispari
			
			//effettua la malloc per creare un nuovo nodo
			tmp=(struct elem*)malloc(sizeof(struct elem));
			//inserisce il valore del nodo con inf dispari
			tmp->inf=l->inf;
			//il valore successivo del nodo copia sarà il successivo dell'elemento copiato
			tmp->next=l->next;
			
			//concatena all'elemento corrente la sua copia
			l->next=tmp;
			
			//ora tmp sarà a tutti gli effetti inserito nella lista poiché il suo next punterà all'elemento successivo di l
			//e il successivo di l sarà proprio tmp
		}
		
	}

	return l;
}
