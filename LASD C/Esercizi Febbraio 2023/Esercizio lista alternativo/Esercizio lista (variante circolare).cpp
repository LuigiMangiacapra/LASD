/*Date due liste doppiamente puntate circolare eliminare dalla prima gli elementi pari e dalla seconda gli elementi dispari*/

#include <stdio.h>
#include <stdlib.h>

struct elem{
	int info;
	struct elem* next;
	struct elem* prev;
};

struct elem* crea_lista(int n);
void stampa_lista(struct elem* lista, struct elem* testa);
struct elem* elimina_pari(struct elem* lista1, struct elem* testa, int n);
struct elem* elimina_dispari(struct elem* lista2, struct elem* testa, int n);

int main(){
	int n;
	struct elem* lista1, *lista2;
	printf("Inserire grandezza lista\n");
	scanf("%d", &n);
	lista1 = crea_lista(n);
	stampa_lista(lista1, lista1);
	printf("\n");
	lista2 = crea_lista(n);
	stampa_lista(lista2, lista2);
	
	lista1 = elimina_pari(lista1, lista1, n);
	
	stampa_lista(lista1, lista1);
	printf("\n");
	
	
	lista2 = elimina_dispari(lista2, lista2, n);

	
	stampa_lista(lista2, lista2);
	
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
		
		for(int i=1; i<n; i++){
			punt->next = (struct elem*)malloc(sizeof(struct elem));
			punt->next->prev = punt;
			punt = punt->next;
			printf("Inserire elemento\n");
			scanf("%d", &punt->info);
		}
		punt->next = p;
		p->prev = punt;
	}
	
	return p;
}



void stampa_lista(struct elem* p, struct elem* testa){
	printf("\nlista ");
	
	while(p->next != testa){
		printf(" ---> ");
		printf("%d", p->info); /* visualizza l'informazione */
		
		p = p->next;
	}
	printf(" ---> ");
	printf("%d", p->info);
	printf("\n");
}



struct elem* elimina_pari(struct elem* lista, struct elem* testa, int n) {
	struct elem* tmp;
    if (n == 0) {
        return testa;
    }
    
    //Se la lista contiene un solo elemento
    if(lista == lista->next){
    	if(lista->info % 2 == 0){
    		return NULL;
		}
		else{
			return testa;
		}
	}
    
    if (lista->info % 2 == 0) {
        tmp = lista;
        
        //Se l'elemento da eliminare non si trova in testa
        if (lista != testa) {
            lista->prev->next = lista->next;
        } 
		else {
            testa = lista->next;
        }
        
        //Se l'elemento da eliminare non è l'ultimo
        if (lista->next != testa) {
            lista->next->prev = lista->prev;
        }
        else{
        	testa->prev = lista->prev;
        	lista->prev->next = testa;
		}
        
        lista = lista->next;
        free(tmp);
    } 
	else {
        lista = lista->next;
    }
    
    n = n - 1;
    elimina_pari(lista, testa, n);
    
    return testa;
}




struct elem* elimina_dispari(struct elem* lista, struct elem* testa, int n) {
	struct elem* tmp;
    if (n == 0) {
        return testa;
    }
    
    //Se la lista contiene un solo elemento
    if(lista == lista->next){
    	if(lista->info % 2 != 0){
    		return NULL;
		}
		else{
			return testa;
		}
	}
    
    if (lista->info % 2 != 0) {
        tmp = lista;
        
        //Se l'elemento da eliminare non si trova in testa
        if (lista != testa) { 
            lista->prev->next = lista->next;
        }
		else {
            testa = lista->next;
        }
        
        //Se l'elemento da eliminare non è l'ultimo
        if (lista->next != testa) {
            lista->next->prev = lista->prev;
        }
        else{
        	testa->prev = lista->prev;
        	lista->prev->next = testa;
		}
        
        lista = lista->next;
        free(tmp);
    } 
	else {
        lista = lista->next;
    }
    
    n = n - 1;
    elimina_dispari(lista, testa, n);
     
    return testa;
}


