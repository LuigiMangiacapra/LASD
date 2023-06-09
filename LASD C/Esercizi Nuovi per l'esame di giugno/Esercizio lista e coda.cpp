/*Creare una lista doppiamente puntata circolare e una coda, eliminare dalla lista tutti gli elementi dispari e sostituire tutti gli elementi pari della coda con gli elementi eliminati dalla lista*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

struct nodo{
	int info;
	struct nodo* next;
	struct nodo* prev;
};

struct nodo* crea_lista(int numero_elementi);
void print_lista_dopp(struct nodo *p);
void inserisci_coda(int Q[], int numero_elementi);
void inizializza_coda(int Q[]);
void enqueue(int Q[], int elem);
int dequeue(int Q[]);
void stampa_coda(int Q[]);
void funzione_esercizio(int Q[], struct nodo** lista, int n);

int main(){
	struct nodo* lista = NULL;
	int numero_elementi_lista;
	
	//Inserimento lista
	printf("Inserisci numero di elementi della lista\n");
	scanf("%d", &numero_elementi_lista);
	lista = crea_lista(numero_elementi_lista);
	print_lista_dopp(lista);
	
	printf("\n");
	
	int Q[MAX + 2];
	int numero_elementi_coda;
	//Inserimento coda
	printf("Inserire numero di elementi della coda\n");
	scanf("%d", &numero_elementi_coda);
	inizializza_coda(Q);
	inserisci_coda(Q, numero_elementi_coda);
	stampa_coda(Q);
	
	printf("\n\n");
	
	//Esercizio
	printf("Lista e coda dopo le modifiche\n\n");
	funzione_esercizio(Q, &lista, numero_elementi_lista);
	
	print_lista_dopp(lista);

	
	stampa_coda(Q);
}


struct nodo* crea_lista(int numero_elementi){
	struct nodo* lista = NULL;
	struct nodo* scorri = NULL;
	int i;
	
	if(numero_elementi == 0){
		lista = NULL;
	}
	else{
		lista = (struct nodo*)malloc(sizeof(struct nodo));
		printf("Inserisci primo elemento: ");
		scanf("%d", &lista->info);
		scorri = lista;
		lista->prev = NULL;
		
		for(i = 1; i < numero_elementi; i++){
			scorri->next = (struct nodo*)malloc(sizeof(struct nodo));
			scorri->next->prev = scorri;
			scorri = scorri->next;
			printf("Inserire l'elemento %d: ", i);
			scanf("%d", &scorri->info);
		}
		scorri->next = lista;
		lista->prev = scorri;
	}
	return lista;
}


void print_lista_dopp(struct nodo *p) {
	if (p == NULL) {
        printf("La lista è vuota\n");
        return;
    }
    
    struct nodo* start = p;
    
    do {
        printf("%d", p->info); /* visualizza l'informazione */
        printf(" ---> ");
        p = p->next;
    } while (p != start);
    
    printf("...\n\n");
} 




void inserisci_coda(int Q[], int numero_elementi){
	int elem;
	if(numero_elementi != 0){
		printf("Inserire elemento nella coda: ");
		scanf("%d", &elem);
		enqueue(Q, elem);
		numero_elementi--;
		inserisci_coda(Q, numero_elementi);
		
	}
}


void stampa_coda(int Q[]){
	int elem;
	if(Q[0] != 0){
		elem = dequeue(Q);
		printf("|%d| ", elem);
		stampa_coda(Q);
		enqueue(Q, elem);
	}
}


void inizializza_coda(int Q[]){
	Q[0] = 0;
	Q[MAX + 1] = 1;
}

void enqueue(int Q[], int elem){
	Q[Q[MAX + 1]] = elem;
	if(Q[0] == 0){
		Q[0] = 1;
	}
	Q[MAX + 1] = (Q[MAX + 1] % MAX) + 1;
	
}

int dequeue(int Q[]){
	int elem = Q[Q[0]];
	Q[0] = (Q[0] % MAX) + 1;
	
	if(Q[0] == Q[MAX + 1]){
		Q[0] = 0;
		Q[MAX + 1] = 1;
	}
	return elem;
}


void funzione_esercizio(int Q[], struct nodo** lista, int n){
	int elem;
	struct nodo* tmp;
	int dispari = 0;
	if(Q[0] != 0 && n != 0){
		
		if ((*lista)->info % 2 != 0) {
			dispari = (*lista)->info;
            tmp = *lista;
            
            //Quando dobbiamo eliminare il nodo 'nodo' dobbiamo modificare tutti i puntatori verso di lui
            //1) Modifica il puntatore successivo del precedente di 'nodo' con il successivo di 'nodo'
            (*lista)->prev->next = (*lista)->next;
            
			//2) Modifica il precedente del successivo di 'nodo' con il precedente di 'nodo'
            (*lista)->next->prev = (*lista)->prev;
            *lista = (*lista)->next;
            free(tmp);
        } 
		else {
            *lista = (*lista)->next;
        }
		
		elem = dequeue(Q);
		n--;
		funzione_esercizio(Q, &((*lista)->next), n);
		
		if(elem % 2 == 0){
			enqueue(Q, dispari);
		}
		else{
			enqueue(Q, elem);
		}
		
	}
}

