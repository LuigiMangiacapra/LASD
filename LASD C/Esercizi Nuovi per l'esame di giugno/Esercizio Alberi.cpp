/*
Creare una funzione che prende due alberi, controlla se entrambi sono ABR e elimina dal primo tutti gli elementi pari e dal secondo tutti i dispari
*/

#include <stdio.h>
#include <stdlib.h>

struct tree {
	int info;
	struct tree* sinistro;
	struct tree* destro;
};

struct tree* inserisci_nodo(struct tree* albero, int elem);
void stampa_albero(struct tree* albero);
void funzione_esercizio(struct tree** albero, struct tree** albero2);
struct tree* elimina(struct tree* radice, int k);
struct tree* elimina_radice(struct tree* radice);
struct tree* stacca_minimo(struct tree *radice, struct tree *padre);


int main(){
	
	int numero_elementi, numero_elementi2, i=0, j=0, elem, elem2;
	struct tree* albero = NULL, *albero2 = NULL;
	
	printf("Inserimento primo Albero\n");
	scanf("%d", &numero_elementi);
	
	while(i < numero_elementi){
		printf("Inserire %d elemento: \n", i+1);
		scanf("%d", &elem);
		albero = inserisci_nodo(albero, elem);
		i++;
	}
	

	printf("Inserimento secondo Albero\n");
	scanf("%d", &numero_elementi2);
	
	while(j < numero_elementi2){
		printf("Inserire %d elemento: \n", j+1);
		scanf("%d", &elem2);
		albero2 = inserisci_nodo(albero2, elem2);
		j++;
	}
	
	
	stampa_albero(albero);
	
	printf("\n");
	
	stampa_albero(albero2);
	
	printf("\n");
	
	funzione_esercizio(&albero, &albero2);
	
	
	stampa_albero(albero);
	
	printf("\n");
	
	stampa_albero(albero2);

}

struct tree* inserisci_nodo(struct tree* albero, int elem){

	if(albero == NULL){
		struct tree* new_nodo = (struct tree*)malloc(sizeof(struct tree));
        if (new_nodo == NULL) {
            perror("Allocazione non possibile");
            exit(1);
        }
        new_nodo->info = elem;
        new_nodo->sinistro = NULL;
        new_nodo->destro = NULL;
        return new_nodo;
	}
	else{
		if(elem < albero->info)
			albero->sinistro = inserisci_nodo(albero->sinistro, elem);
		else if(elem > albero->info)
			albero->destro = inserisci_nodo(albero->destro, elem);
	}
	
	return albero;
}


void stampa_albero(struct tree* albero){
	if(albero != NULL){
		
		stampa_albero(albero->sinistro);
		printf("|%d| ", albero->info);
		stampa_albero(albero->destro);
		
	}
}


void funzione_esercizio(struct tree** albero, struct tree** albero2){
	
	int bst = 1, bst2 = 1;

    // Controlla se entrambi gli alberi sono ABR
    // Aggiungi controlli per verificare l'ordinamento dei nodi nell'albero

    if (*albero == NULL) {
        bst = 1;
    } 
	else if ((*albero)->sinistro != NULL && (*albero)->sinistro->info > (*albero)->info) {
        bst = 0;
    } 
	else if ((*albero)->destro != NULL && (*albero)->destro->info < (*albero)->info) {
        bst = 0;
    }

    if (*albero2 == NULL) {
        bst2 = 1;
    } 
	else if ((*albero2)->sinistro != NULL && (*albero2)->sinistro->info > (*albero2)->info) {
        bst2 = 0;
    } 
	else if ((*albero2)->destro != NULL && (*albero2)->destro->info < (*albero2)->info) {
        bst2 = 0;
    }

    if (bst == 1 && bst2 == 1) {
    	if (*albero != NULL) {
	        // Elimina elementi pari dal primo albero
	        if ((*albero)->info % 2 == 0) {
	            *albero = elimina(*albero, (*albero)->info);
	        }
	        funzione_esercizio(&(*albero)->sinistro, albero2);
            funzione_esercizio(&(*albero)->destro, albero2);
		}
	        // Elimina elementi dispari dal secondo albero
	    if (*albero2 != NULL) {
	        // Elimina elementi pari dal primo albero
	        if ((*albero2)->info % 2 != 0) {
	            *albero2 = elimina(*albero2, (*albero2)->info);
	        }
	        funzione_esercizio(albero, &(*albero2)->sinistro);
            funzione_esercizio(albero, &(*albero2)->destro);
		}
        
    }
	
}


//Elimina elemento dall'albero
struct tree* elimina(struct tree* radice, int k){
	if(radice!=NULL){//se l'albero non è vuoto o si è arrivati ad un nodo NULL (figlio di una foglia)
		//cerca nel sottoalbero destro
		if(k>radice->info)
			radice->destro=elimina(radice->destro, k);
		//cerca nel sottoalbero sinistro
		else if(k<radice->info){
			radice->sinistro=elimina(radice->sinistro, k);
		}
		else{
			//vuol dire che l'elemento è stato trovato 
			radice=elimina_radice(radice);//permette di eliminare l'elemento trovato, a prescindere da dove si trovi
		}
	}
	return radice;
}



//elimina il nodo dell'albero
struct tree* elimina_radice(struct tree* radice){
	struct tree* tmp;
	if(radice!=NULL){
		//Se il nodo da eliminare ha un solo sottoalbero(figlio) o entrambi NULL
		if(radice->destro==NULL || radice->sinistro==NULL){
			tmp=radice;//salva il nodo da eliminare in tmp
			if(radice->destro != NULL)//se ha figlio destro, sposta il puntatore su quest'ultimo rendendolo il nuovo figlio del padre dell'elemento eliminato
				radice=radice->destro;
			else if(radice->sinistro!=NULL)//se ha un figlio sinistro, sposta il puntatore su quest'ultimo...(come sopra)
				radice=radice->sinistro;
			free(tmp);//elimina l'elemento dopo aver spostato il riferimento del puntatore al nodo figlio
			
		}
		//Se il nodo da eliminare ha due sottoalberi(figli)
		else{//(radice->destro!=NULL && radice->sinistro!=NULL)
			tmp=stacca_minimo(radice->destro, radice);//Trova il minimo tra i massimali (l'estremo superiore: elemento con valore prossimo alla radice, per sostituirla)
			radice->info=tmp->info;//sovrascrive il nodo da eliminare con quello minimo
			free(tmp);//elimina l'elemento minimo(alla fine, sostituendo l'elemento minimo a quello da eliminare e eliminando quello minimo, si è eliminato il nodo designato)
		}
	}
	return radice;
}


//stacca l'elemento minimo o lo sostituisce all'elemento eliminato(radice->inf=tmp->inf in elimina_radice)
struct tree* stacca_minimo(struct tree *radice, struct tree *padre){
	struct tree* ret;
	if(radice != NULL){
		if(radice->sinistro != NULL){//naviga l'albero controllando sempre sui figli sinistri, se trova un nodo senza figlio sinistro allora è minimo
			radice = stacca_minimo(radice->sinistro,radice);//Quando bisogna navigare senza modificare non bisogna assegnare a radice->sinistro perché non si modifica nulla
		}												  //trova l'elemento minimo e lo assegna a "radice"
		else{
			ret=radice;
				
			if(padre->sinistro == radice)//se il figlio sinistro di 'padre' è minimo allora il nuovo figlio sinistro di 'padre' sarà il vecchio figlio destro del minimo
				padre->sinistro = radice->destro;
			else if(padre->destro == radice)//l'unica possibilità in cui il figlio destro sia minimo è quando è minimo il primo nodo del sottoalbero destro che stiamo visitando
				padre->destro = radice->destro;
		}		
	
	}
	return ret;	
}
