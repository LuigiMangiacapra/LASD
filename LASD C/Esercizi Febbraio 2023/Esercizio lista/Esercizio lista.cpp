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
struct elem* elimina_pari(struct elem* lista1, struct elem* testa);
struct elem* elimina_dispari(struct elem* lista2, struct elem* testa);

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
	
	lista1 = elimina_pari(lista1, lista1);
	lista2 = elimina_dispari(lista2, lista2);

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



struct elem* elimina_pari(struct elem* lista, struct elem* testa) {
	struct elem* tmp;
    if (lista == NULL) {
        return testa;
    }
    
    if (lista->info % 2 == 0) {
        tmp = lista;
        
        //Reimposta il successivo dell'elemento precedente a quello eliminato, se l'elemento precedente � nullo allora ci troviamo in testa
        if (lista->prev != NULL) {
            lista->prev->next = lista->next;
        } 
		else {
            testa = lista->next;
        }
        
        //Reimposta il precedente dell'elemento successivo all'elemento eliminato
        if (lista->next != NULL) {
            lista->next->prev = lista->prev;
        }
        
        lista = lista->next;
        free(tmp);
    } 
	else {
        lista = lista->next;
    }
    
    elimina_pari(lista, testa);
    
    return testa;
}



//ricorsiva
struct elem* elimina_dispari(struct elem* lista, struct elem* testa) {
	struct elem* tmp;
    if (lista == NULL) {
        return testa;
    }
    
    if (lista->info % 2 != 0) {
        tmp = lista;
        
        if (lista->prev != NULL) { //si controlla se prev non � NULL perch� se lo fosse allora staremo parlando dell'elemento in testa
            lista->prev->next = lista->next;
        }
		else {
            testa = lista->next;
        }
        
        if (lista->next != NULL) {
            lista->next->prev = lista->prev;
        }
        
        lista = lista->next;
        free(tmp);
    } 
	else {
        lista = lista->next;
    }
    
    elimina_dispari(lista, testa);
    
    return testa;
}


//iterativa
struct elem* elimina_dispari(struct elem* lista, struct elem* testa, int elem) {
	
    struct elem* prev = NULL;
    struct elem* curr = testa
    
    while (curr != NULL && curr->info != elem) {
        prev = curr;
        curr = curr->next;
    }
 
    if (curr == NULL) {
        //elemento non trovato
        return;
    }
 
    if (prev == NULL) {
        // L'arco � il primo dell'elenco di adiacenza
        testa = curr->next;
    } 
	else {
        // L'arco non � il primo dell'elenco di adiacenza
        prev->next = curr->next;
        curr->next->prev = prev;
    }
 
    // Libera la memoria dell'arco eliminato
    free(curr);
    
    return testa;
}



