/*
	Creare due liste doppiamente puntate: 
	- stampare le liste
	- ordinare la lista1
	- Inserire il nodo dispari della prima lista in testa alla seconda
*/

#include <stdio.h>
#include <stdlib.h>

struct nodo* crea_lista();
void funzione_esercizio(struct nodo** lista1, struct nodo** lista2);
void print_lista(struct nodo* lista);
void inserisci_testa(struct nodo** list1, struct nodo** list2);


struct nodo{
	int info;
	struct nodo* next;
	struct nodo* prev;
};

int main(){
	int n1, n2;
	struct nodo* lista1, *lista2;
	
	lista1 = crea_lista();
	lista2 = crea_lista();
	
	printf("lista1: ");
	print_lista(lista1);
	
	printf("\n");
	
	printf("lista2: ");
	print_lista(lista2);
	
	funzione_esercizio(&lista1, &lista2);
	
	printf("\n");
	
	printf("lista1: ");
	if(lista1 != NULL)
		print_lista(lista1);
	else
		printf("lista vuota\n");
	
	
	printf("\n");

	
	printf("lista2: ");
	if(lista2 != NULL)
		print_lista(lista2);
	else
		printf("lista vuota\n");

}


struct nodo* crea_lista(){
	struct nodo* punt, *testa;
	int n;
	
	printf("Indicare il numero di elementi della lista\n");
	scanf("%d", &n);
	
	if(n == 0){
		testa = NULL;
	}
	else{
		testa = (struct nodo*)malloc(sizeof(struct nodo));
		printf("Inserire primo valore\n");
		scanf("%d",&testa->info);
		punt = testa;
		punt->prev = NULL;
		
		for(int i = 1; i < n; i++){
			punt->next = (struct nodo*) malloc(sizeof(struct nodo));
			punt->next->prev = punt;
			punt = punt->next;
			printf("Inserire valore\n");
			scanf("%d",&punt->info);
		}
		punt->next = NULL;
		
	}
	return testa;
}


void funzione_esercizio(struct nodo** list1, struct nodo** list2){

   	int temp;
    struct nodo* tmp;

    if (*list1 != NULL && *list2 != NULL) {
    	
        if (*list1 != NULL ) {
        	
            if ((*list1)->info % 2 == 0) {
            	//Ordina la lista1
                if ((*list1)->next != NULL && (*list1)->info > (*list1)->next->info) {

                    temp = (*list1)->info;
                    (*list1)->info = (*list1)->next->info;
                    (*list1)->next->info = temp;
                
				}
            	funzione_esercizio(&(*list1)->next, list2);
            	funzione_esercizio(&(*list1)->next, list2);
			} 
			else {
				//Sposta gli elementi dispari dalla lista1 alla lista2
                tmp = *list1;
                *list1 = (*list1)->next;
                tmp->next = *list2;
                *list2 = tmp;
                funzione_esercizio(list1, list2);
            }  
            
        }
        
    }
	    
}



void print_lista(struct nodo* lista){
	if(lista != NULL){
		printf("|%d| ", lista->info);
		print_lista(lista->next);
	}
}
