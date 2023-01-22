/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L, elimini tutti gli elementi divisibili 
per 10.

*/

#include <stdio.h>
#include <malloc.h>

struct elem *crea_lista();
void visualizza_lista(struct elem *lista);
struct elem *delete_10(struct elem *l);

struct elem{
	int inf;
	struct elem *next;
};

int main(){
	
	struct elem *lista; //puntatore che si collega alla struct per creare la lista
	lista=crea_lista();
	visualizza_lista(lista);
	lista=delete_10(lista);
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
		testa=(struct elem *)malloc(sizeof(struct elem));//Nuova locazione di memoria puntata da "testa" che rappresenta la testa della lista
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
	printf("\n lista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 




struct elem *delete_10(struct elem *l){
	struct elem *tmp;
	//CASO BASE
	if (l!=NULL){
		//scorre ricorsivamente la lista fino a l=NULL
		l->next = delete_10(l->next);
		
		if(l->inf%10==0){
			tmp=l;
			l=l->next;//Non shifta soltanto ma riassegna il next del precedente. Mentre prima il next del precedente era l adesso sarà l->next
			free(tmp);
		}
		//ERRORE!
		//l->next = delete_10(l->next); PERCHE' NON DOPO?	
		//Perché qualsiasi modifica ad un nodo potrebbe fargli perdere il riferimento all'elemento successivo
		//soprattutto nel momento in cui si eliminano nodi o se ne aggiungono di nuovi nella lista
		//quindi se si vuole modificare una lista o una struttura dati simile bisogna farlo dopo la chiamata ricorsiva
	}
		
	return l;
	
}


