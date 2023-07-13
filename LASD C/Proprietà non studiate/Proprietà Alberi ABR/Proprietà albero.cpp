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

int main() {
    int size, elem, max = 0, bst = 1, trova = 0;
    struct nodo* radice = NULL;
    struct radice_sub;
    int altezza;
    
    printf("Inserire grandezza albero\n");
    scanf("%d", &size);

    while (size > MAX) {
        printf("Inserire max %d elementi\n", MAX);
        scanf("%d", &size);
    }

    while (size != 0) {

        printf("Inserire elemento da inserire\n");
        scanf("%d", &elem);

        radice = crea_albero(radice, elem);
        size--;
    }

    stampa_albero(radice);
    printf("\n");
    
    printf("Altezza albero\n");
    altezza = altezza_albero(radice);
    
    printf("L'altezza dell'albero e' %d\n", altezza);
    
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

int altezza_albero(struct nodo* radice) {
    if (radice == NULL) {
        return 0;
    } 
	else {
		printf("DISCESA: radice: %d\n", radice->info);
        int altezza_sinistro = altezza_albero(radice->sinistro);
        int altezza_destro = altezza_albero(radice->destro);
		printf("RISALITA: altezza_sinistro: %d, altezza_destro: %d\n", altezza_sinistro, altezza_destro);
		
        if (altezza_sinistro > altezza_destro) {
        	printf("altezza_sinistro > altezza_destro\n");
            return altezza_sinistro + 1;
        } 
		else {
        	printf("altezza_sinistro <= altezza_destro\n");
            return altezza_destro + 1;
        }
    }
}
