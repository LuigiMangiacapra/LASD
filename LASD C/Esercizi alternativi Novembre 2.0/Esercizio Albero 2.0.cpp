/* 
	Dato un albero e due chiavi k1 e k2, scrivere una funzione che verifichi che l'albero
	sia binario di ricerca e verifichi che il massimo del sottoalbero radicato in k1 sia multiplo
	di k2
*/

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
int funzione_esercizio(struct nodo* radice, int elem, int bst, int* max, struct nodo* radice_sub);


int main() {
    int size, elem, max = 0, bst = 1, trova = 0;
    struct nodo* radice = NULL;
    struct radice_sub;
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
    
    printf("Inserire radice sottoalbero\n");
    scanf("%d", &trova);
    
    max = funzione_esercizio(radice, trova, bst, &max, radice);
    printf("max: %d\n", max);

    if (max != 0) {
        printf("L'albero e' un ABR e il valore massimo del sottoalbero di %d e' %d\n", trova, max);
        if(max % trova == 0){
        	printf("Il massimo %d e' multiplo della radice %d del sottoalbero\n", max, trova);
		}
		else{
			printf("Il massimo %d non e' multiplo della radice %d del sottoalbero\n", max, trova);

		}
    }
    else {
        printf("L'albero non e' un ABR o il valore massimo del sottoalbero di %d non esiste", trova);
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


int funzione_esercizio(struct nodo* radice, int elem, int bst, int* max, struct nodo* radice_sub) {
    if (radice != NULL) {
        if (radice->sinistro != NULL && radice->sinistro->info > radice->info) {
            bst = 0;
        }
        if (radice->destro != NULL && radice->destro->info < radice->info) {
            bst = 0;
        }
        
        if(bst != 0){
            if (radice->info == elem) {
                radice_sub = radice;
                printf("radice_sub->info (Testa): %d\n", radice_sub->info);
            }
            
            if (radice_sub->destro == NULL) {
                *max = radice_sub->info;
                printf("max: %d\n", *max);
                printf("radice_sub->info: %d\n", radice_sub->info);
            }

            //radice scorre per controllare se l'albero è un ABR, *radice_sub scorre per trovare il massimo a partire da una radice del sottoalbero
            funzione_esercizio(radice->destro, elem, bst, max, radice_sub->destro);
            funzione_esercizio(radice->sinistro, elem, bst, max, radice_sub);
            
            
        } else {
            printf("L'albero non è un ABR\n'");
            exit(1);
        }
    }
    return *max;
}

