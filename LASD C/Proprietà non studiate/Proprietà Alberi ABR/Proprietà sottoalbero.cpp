#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20 

struct nodo{
	int info;
	struct nodo* destro;
	struct nodo* sinistro;
};

struct nodo* crea_nodo(struct nodo* destro, struct nodo* sinistro, int elem){
	struct nodo* nuovo = (struct nodo*)malloc(sizeof(struct nodo));
	if(nuovo != NULL){
		nuovo->info = elem;
		nuovo->destro = destro;
		nuovo->sinistro = sinistro;
	}
	return nuovo;
}

struct nodo* crea_albero(struct nodo* radice, int elem);
void stampa_albero(struct nodo* radice);
int altezza_albero(struct nodo* radice);
int is_identical(struct nodo* radice1, struct nodo* radice2);
int is_subtree(struct nodo* radice, struct nodo* radice2);

int main() {
    int size, elem, max = 0, bst = 1, trova = 0;
    struct nodo* radice = NULL,* radice2 = NULL;
    struct radice_sub;
    int altezza;
    int size2;
    int sub;
    printf("Inserimento primo albero\n\n");
    printf("Inserire grandezza albero\n");
    scanf("%d", &size);

    while (size > MAX) {
        printf("Inserire max %d elementi\n", MAX);
        scanf("%d", &size);
    }
    
	
    while (size != 0) {

        printf("Inserire elemento\n");
        scanf("%d", &elem);

        radice = crea_albero(radice, elem);
        size--;
    }

    stampa_albero(radice);
    printf("\n");
    
    
    
    printf("Inserimento secondo albero\n\n");
    printf("Inserire grandezza albero\n");
    scanf("%d", &size2);
    
    while (size2 != 0) {

        printf("Inserire elemento\n");
        scanf("%d", &elem);

        radice2 = crea_albero(radice, elem);
        size2--;
    }

    stampa_albero(radice2);
    printf("\n");
   	
   	
   	if (is_subtree(radice, radice2)) {
        printf("Il secondo albero e' un sottoalbero del primo albero.\n");
    } 
	else {
        printf("Il secondo albero non e' un sottoalbero del primo albero.\n");
    }
    
    return 0;
}


struct nodo* crea_albero(struct nodo* radice, int elem) {

    if (radice == NULL) {
        radice = crea_nodo(NULL, NULL, elem);
    }
    else {
        if (radice->info < elem) {
            radice->destro = crea_albero(radice->destro, elem);
        }
        else if (radice->info > elem) {
            radice->sinistro = crea_albero(radice->sinistro, elem);
        }
    }

    return radice;
}
 

void stampa_albero(struct nodo* radice) {

    if (radice != NULL) {
        stampa_albero(radice->sinistro);
        printf("|%d| ", radice->info);
        stampa_albero(radice->destro);
    }

}


int is_identical(struct nodo* radice1, struct nodo* radice2) {
    if (radice1 == NULL && radice2 == NULL) {
        return 1;
    } 
	else if (radice1 == NULL || radice2 == NULL) {
        return 0;
    } 
	else if (radice1->info == radice2->info) {
        return is_identical(radice1->sinistro, radice2->sinistro) &&
               is_identical(radice1->destro, radice2->destro);
    } 
	else {
        return 0;
    }
}

int is_subtree(struct nodo* radice, struct nodo* radice2) {
    if (radice == NULL) {
        return 0;
    } 
	else if (is_identical(radice, radice2)) {
        return 1;
    } 
	else {
        return is_subtree(radice->sinistro, radice2) ||
               is_subtree(radice->destro, radice2);
    }
}


