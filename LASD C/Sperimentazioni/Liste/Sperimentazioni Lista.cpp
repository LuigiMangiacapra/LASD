#include <stdio.h>
#include <malloc.h>

struct el
{
	struct el *prev;
	int inf;
	struct el *next;
};

struct el *crea_lista(int n);
void visualizza_lista(struct el *lista);
void print_lista_dopp(struct el *p, int n);
void esercizio_sperim(struct el* lista);
void esercizio_sperim2(struct el* lista, struct el* lista2);

int main(){
	struct el *lista, *lista2;
	int valore,valore2;
	int liste = 1;
	struct el* testa = NULL;
	int n = 0, n2 = 0;
	int elem = 0;
	int numero_elementi = 0;
	
	printf("Specificare numero di elementi prima lista\n");
	scanf("%d", &n);
	lista=crea_lista(n); 
	visualizza_lista(lista);
	
	printf("Specificare numero di elementi seconda lista\n");
	scanf("%d", &n2);
	lista2=crea_lista(n2); 
	visualizza_lista(lista2);
	
	
	printf("\nStampa lista1\n");
	visualizza_lista(lista);
	
	printf("\nStampa lista2\n");
	visualizza_lista(lista2);
	
	
	esercizio_sperim2(lista, lista2);
	
	
}


/*Lista doppiamente puntata*/
struct el *crea_lista(int n) {
    struct el *p, *punt;
    int i;
    if(n==0) {
        p = NULL;
    } else {
        /* creazione primo elemento */
        p = (struct el*)malloc(sizeof(struct el));
        printf("\nInserisci il primo valore: ");
        scanf("%d", &p->inf);
        punt = p;
        p->prev = NULL;
        for(i=2; i<=n; i++) {
            punt->next = (struct el *)malloc(sizeof(struct el));
            punt->next->prev = punt;
            punt = punt->next;
            printf("\nInserisci il %d elemento: ", i);
            scanf("%d", &punt->inf);
        } // chiudo il for
        punt->next = NULL;
    } // chiudo l'if-else
    return(p); // ritorno il puntatore alla testa
} // chiudo la funzione


void visualizza_lista(struct el *p) {
	printf("\nlista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 



/*void esercizio_sperim(struct el* lista){
	
	if(lista == NULL){
		printf("NULL\n");
		return;
	}
		
	
	printf("lista: %d\n", lista->inf);
	
	esercizio_sperim(lista->next);
	esercizio_sperim(lista->next);
	
}*/

void esercizio_sperim2(struct el* lista, struct el* lista2){
	
	if(lista == NULL || lista2 == NULL){
		printf("NULL\n");
		
		return;
	}
		
	
	printf("lista: %d\n", lista->inf);
	printf("lista2: %d\n", lista2->inf);
	
	if(lista->next == NULL)
		lista2 = lista;
	
	esercizio_sperim2(lista, lista2->prev);
	
	esercizio_sperim2(lista->next, lista2);
	
	
	
}
