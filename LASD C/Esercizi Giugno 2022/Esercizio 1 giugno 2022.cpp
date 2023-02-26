/*
Scrivere una funzione che, data una stringa s, restituisca una lista L doppiamente puntata contenente
tutte le vocali di s in ordine inverso a come compaiono in s.
Inoltre, si scriva una funzione ricorsiva che elimini da L le ripetizioni consecutive.
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct elem *crea_lista(char* str);
void visualizza_lista(struct elem *lista);
struct elem *delete_repeat(struct elem *l, struct elem *nx);

struct elem{
	char inf;
	struct elem *next, *prev;
};

int main(){
	
	struct elem *lista;
	char* str = "esempio";
	lista=crea_lista(str);
	visualizza_lista(lista);
	lista=delete_repeat(lista,lista->next);
	visualizza_lista(lista);

}


struct elem *crea_lista(char* stringa){
	struct elem *testa, *punt;
	int i, n;
	n = strlen(stringa);
	
	if(n==0){
		testa=NULL;
	}
	else{
		if(stringa[n-1]=='a' || stringa[n-1]=='e' || stringa[n-1]=='i' || stringa[n-1]=='o' || stringa[n-1]=='u'){
			testa=(struct elem *)malloc(sizeof(struct elem));//Nuova locazione di memoria puntata da "testa" che rappresenta la testa della lista
			if(testa != NULL){
				testa->inf = stringa[n-1];
				punt=testa;
				punt->prev=NULL;
			}
			else
				printf("Impossibile allocare memoria!\n");
				
		}
		
		for(i=n-2;i>=0;i--){
			if(stringa[i]=='a' || stringa[i]=='e' || stringa[i]=='i' || stringa[i]=='o' || stringa[i]=='u'){
				punt->next=(struct elem *)malloc(sizeof(struct elem));
				if(punt->next != NULL){
					punt->next->prev=punt;
					punt=punt->next;
					punt->inf = stringa[i];
				}
				else
					printf("Impossibile allocare memoria!\n");
			}
		}
		punt->next=NULL;
	
	}
	return(testa);
}



void visualizza_lista(struct elem *p) {
	printf("\n lista ---> ");
	while(p != NULL){
		printf("%c", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 




struct elem *delete_repeat(struct elem *l1, struct elem *l2){//la funzione prende in input un puntatore al primo elemento e l'altro al secondo
	struct elem *tmp;
	//CASO BASE
	if(l1->next && l2!=NULL){
		//scorre ricorsivamente la lista fino a l1=NULL e l2=NULL
		l1->next = delete_repeat(l1->next, l2->next); 
		
		if(l1->inf == l2->inf){
			tmp=l1;
			l1=l1->next;//Non shifta soltanto ma riassegna il next del precedente. Mentre prima il next del precedente era l adesso sarà l->next
			free(tmp);
		}
	}
		
	return l1; //restituire l1 perché è il puntatore che parte dalla testa della lista
	
}


