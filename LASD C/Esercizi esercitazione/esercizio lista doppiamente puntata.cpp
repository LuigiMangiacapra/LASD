/*
	creare una lista doppiamente puntata e sostituire ogni coppia successiva di valori dispari con
	la media di tutti i valori pari
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

struct nodo{
	int inf;
	struct nodo* next;
	struct nodo* prev;
};

struct nodo* crea_lista(int n, struct nodo* prec, struct nodo* curr);
void stampa_lista(struct nodo* lista);
double mediaPariLista(struct nodo* head);
void replace_odd_pairs_helper(struct nodo *node, double mean);
void replace_odd_pairs(struct nodo *head);
double mediaPariLista(struct nodo* node, int sum, int count);



int main(){
	int n_elem;
	struct nodo *prec = NULL, *curr = NULL;
	struct nodo* lista;
	printf("inserire il quantitativo di elementi da inserire\n");
	scanf("%d", &n_elem);
	
	while(n_elem > MAX){
		printf("inserire massimo %d elementi \n", MAX);
		scanf("%d", &n_elem);
	}
	
	lista = crea_lista(n_elem, prec, curr);
	stampa_lista(lista);
	printf("\n");
	replace_odd_pairs(lista);
	stampa_lista(lista);
}


struct nodo* crea_lista(int n, struct nodo* prec, struct nodo* curr){

	if(n != 0){
		curr = (struct nodo*)malloc(sizeof(struct nodo*));
		printf("Inserire valore\n");
		scanf("%d", &curr->inf);
		
		curr->next = NULL;
		curr->prev = prec;
		prec = curr;
		
		n = n - 1;
		curr->next = crea_lista(n, prec, curr->next);
	}
	
	return curr;
	
}


void stampa_lista(struct nodo* lista){
	
	if(lista != NULL){
		printf("|%d| ", lista->inf);
		stampa_lista(lista->next);
	}
}


double mediaPariLista(struct nodo* node, int sum, int count) {
    if (node == NULL) {
        // Caso base: lista vuota
        if (count > 0) {
            return (double)sum / count;
        } else {
            return 0.0;
        }
    }
    if (node->inf % 2 == 0) {
        // Se il valore è pari, aggiungiamolo alla somma e incrementiamo il contatore
        sum += node->inf;
        count++;
    }
    // Chiamiamo la funzione ricorsiva sulla coda della lista
    return mediaPariLista(node->next, sum, count);
}



void replace_odd_pairs_helper(struct nodo *node, double mean) {
    if (node == NULL || node->next == NULL) {
        // Caso base: lista vuota o con un solo elemento
        return;
    }
    if (node->inf % 2 != 0 && node->next->inf % 2 != 0) {
        // Sostituiamo la coppia di valori dispari con la media dei valori pari
        node->inf = (int)mean;
        node->next->inf = (int)mean;
        // Chiamiamo la funzione ricorsiva sulla coppia successiva
        replace_odd_pairs_helper(node->next->next, mean);
    } else {
        // Altrimenti, avanziamo nella lista
        replace_odd_pairs_helper(node->next, mean);
    }
}


void replace_odd_pairs(struct nodo *head) {
	int sum = 0, count = 0;
    double mean = mediaPariLista(head, sum, count);
    replace_odd_pairs_helper(head, mean);
}

