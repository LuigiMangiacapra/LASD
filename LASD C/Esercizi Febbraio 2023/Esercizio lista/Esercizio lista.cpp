/*Date due liste doppiamente puntate eliminare dalla prima gli elementi pari e dalla seconda gli elementi dispari*/

#include <stdio.h>
#include <stdlib.h>

struct elem{
	int info;
	struct elem* next;
	struct elem* prev;
};

struct elem* crea_lista(int n);
void stampa_lista(struct elem* lista);
void elimina_pari_e_dispari(struct elem** lista, struct elem** lista2);

int main(){
	int n;
	struct elem* lista1, *lista2;
	printf("Inserire grandezza lista\n");
	scanf("%d", &n);
	lista1 = crea_lista(n);
	stampa_lista(lista1);
	printf("\n");
	lista2 = crea_lista(n);
	stampa_lista(lista2);
	
	elimina_pari_e_dispari(&lista1, &lista2);

	stampa_lista(lista1);
	printf("\n");
	stampa_lista(lista2);
	
}

struct elem* crea_lista(int n){
	struct elem* p, *punt;
	if(n==0){
		p = NULL;
	}
	else{
		p = (struct elem*)malloc(sizeof(struct elem));
		printf("Inserire primo elemento\n");
		scanf("%d", &p->info);
		punt = p;
		p->prev = NULL;
		
		for(int i=1; i<n; i++){
			punt->next = (struct elem*)malloc(sizeof(struct elem));
			punt->next->prev = punt;
			punt = punt->next;
			printf("Inserire elemento\n");
			scanf("%d", &punt->info);
		}
		punt->next = NULL;
	}
	
	return p;
}



void stampa_lista(struct elem* p){
	printf("\nlista ---> ");
	
	while(p != NULL){
		printf("%d", p->info); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next;
	}
	printf("NULL\n\n"); 
}



//ricorsiva
void elimina_pari_e_dispari(struct elem** lista, struct elem** lista2) {
    struct elem* tmp;
    struct elem* tmp2;
	
	//Se le due liste sono vuote o se si è arrivati con entrambe le liste a NULL
    if ((*lista) == NULL && (*lista2) == NULL) {
        return;
    }

    if ((*lista) != NULL) {//Controlla che la lista1 non sia nulla per poter accedere all'elemento
        if ((*lista)->info % 2 == 0) {//Controlla se l'elemento è pari
            tmp = *lista;
            *lista = (*lista)->next;
			
			//Imposta l'elemento precedente del successivo a NULL in quanto il precedente sarà eliminato
            if (*lista != NULL) {
                (*lista)->prev = NULL;
            }

            free(tmp);
        } 
		else {
            lista = &((*lista)->next);//Prende il successivo del nodo contenuto in (*lista) e assegna l'indirizzo alla variabile lista
        }
    }

    if ((*lista2) != NULL) {//Controlla che la lista1 non sia nulla per poter accedere all'elemento
        if ((*lista2)->info % 2 != 0) {//Controlla se l'elemento è dispari
            tmp2 = *lista2;
            *lista2 = (*lista2)->next;
			
			//Imposta l'elemento precedente del successivo a NULL in quanto il precedente sarà eliminato
            if (*lista2 != NULL) {
                (*lista2)->prev = NULL;
            }

            free(tmp2);
        } 
		else {
            lista2 = &((*lista2)->next);
        }
    }

    elimina_pari_e_dispari(lista, lista2);//Prende il successivo del nodo contenuto in (*lista2) e assegna l'indirizzo alla variabile lista2
}





