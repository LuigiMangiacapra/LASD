
#include <stdio.h>
#include <malloc.h>

struct el
{
	struct el *prev;
	int inf;
	struct el *next;
};

struct el *crea_lista(int n);
struct el *inserisci(struct el*,int);
void visualizza_lista(struct el *lista);
struct el* inserisci_testa(struct el* L, int valore);
void print_lista_dopp(struct el *p, int n);
struct el* elimina(struct el* lista, int elem);

int main(){
	struct el *lista;
	int valore,valore2;
	int liste = 1;
	struct el* testa = NULL;
	int n = 0;
	int elem = 0;
	
	printf("Specificare numero di elementi\n");
	scanf("%d", &n);
	lista=crea_lista(n); 
	visualizza_lista(lista);
	
	printf("Inserire l'elemento da eliminare\n");
	scanf("%d", &elem);
	lista = elimina(lista, elem);
	
	printf("\nStampa lista dopo eliminazione\n");
	visualizza_lista(lista);
}

/*

struct el *crea_lista(int n) {
    struct el *p, *punt;
    int i;
    if(n==0) {
        p = NULL;
    } 
	else {
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
        punt->next = p; // lista circolare: l'ultimo elemento punta alla testa
        p->prev = punt; // la testa punta all'ultimo elemento
    } // chiudo l'if-else
    return(p); // ritorno il puntatore alla testa
} // chiudo la funzione
*/


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


struct el *inserisci(struct el *p, int valore)
{ 
	struct el *nuovo=NULL;
	struct el *testa;
	if (p==NULL) {
		p=(struct el *)malloc(sizeof(struct el));
		p->inf=valore;
		p->prev=NULL; 
		testa=p; 
	}
	else {
		testa=p;
		if (p->next!= NULL) 
			inserisci(p->next, valore);
		nuovo=(struct el *)malloc(sizeof(struct el));
		nuovo->prev=p;
		nuovo->inf=valore;
		nuovo->next = NULL; 
	}
	p->next=nuovo; 
	return testa;
}

void visualizza_lista(struct el *p) {
	printf("\nlista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 


//inserimento in testa
struct el* inserisci_testa(struct el* L, int valore){
	struct el*punt, *new_elem;
	
	new_elem=(struct el*)malloc(sizeof(struct el*));
	new_elem->inf=valore;
	new_elem->prev=NULL;
	new_elem->next=L;
	L = new_elem;

	return L;
}


struct el* elimina(struct el* lista, int elem) {
    struct el* tmp;
	printf("|%d| ", lista->inf);
	//Se le due liste sono vuote o se si è arrivati con entrambe le liste a NULL
    if (lista == NULL) {
    	printf("NULL");
        return lista;
    }
    else{
        if (lista->inf == elem) { 
        	tmp = lista;
        	if(lista->prev != NULL){
        		lista->prev->next = lista->next;
			}
			if(lista->next != NULL){
				lista->next->prev = lista->prev;
			}

            lista = lista->next;
            free(tmp);
            
            //lista = deleteNode(lista, elem); //Se si vogliono eliminare duplicati
        } 
		else {
            lista->next = elimina(lista->next, elem);
        }
    }

    
    return lista;
}


