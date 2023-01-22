

#include <stdio.h>
#include <malloc.h>

struct elem *crea_lista();
void visualizza_lista(struct elem *lista);

struct elem{
	int inf;
	struct elem *next;
};

int main(){
	
	struct elem *lista; //puntatore che si collega alla struct per creare la lista
	lista=crea_lista();
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
		testa=(struct elem *)malloc(sizeof(struct elem)); //crea uno spazio in memoria per la testa della lista
		printf("inserire primo elemento\n");
		scanf("%d",&testa->inf);
		punt=testa; //puntatore che viene utilizzato per evitare che il puntatore alla testa si sposti
		for(i=2;i<=n;i++){ //for che parte dalla seconda posizione perché è già stato creato il nodo per la testa della lista
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
	printf("\n lista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 

