/*
	Eliminare ogni nodo che abbia valore dispari
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

struct nodo{
	int inf;
	struct nodo* sinistro, *destro;
};

//Macro
struct nodo* crea_nodo(struct nodo* sinistro, struct nodo* destro, int elem){
	
	struct nodo* punt = NULL;
	punt = (struct nodo*)malloc(sizeof(struct nodo));
	if(punt != NULL){//controllare sempre che l'allocazione è stata fatta correttamente
		punt->inf = elem;
		punt->sinistro = sinistro;
		punt->destro = destro;
	}
	return punt;
}


struct nodo* inserisci(struct nodo* radice, int elem);
struct nodo* elimina(struct nodo* radice, int elem);
struct nodo* elimina_radice(struct nodo* radice);
struct nodo* stacca_minimo(struct nodo*radice, struct nodo*padre);
struct nodo* elimina_dispari(struct nodo* radice);
void stampa_in_ordine(struct nodo*radice);


int main(){
	int n = 0, elem = 0, count = 0;
	struct nodo* radice = NULL;
	
	printf("Inserire il numero di elementi da inserire\n");
	scanf("%d", &n);
	
	while(n){
		count++;
		printf("Inserici elemento %d:\n",count);
		scanf("%d",&elem);
		radice=inserisci(radice, elem);
		n--;
	}
	stampa_in_ordine(radice);
	printf("\n");
	radice=elimina_dispari(radice);
	stampa_in_ordine(radice);
	
	return 0;
}


struct nodo* inserisci(struct nodo* radice, int elem){
	if(radice == NULL){
		radice = crea_nodo(NULL, NULL, elem);
	}
	else{
		if(elem < radice->inf)
			radice->sinistro = inserisci(radice->sinistro, elem);
		else if(elem > radice->inf)
			radice->destro = inserisci(radice->destro, elem);

	}
	return radice;
}


struct nodo* elimina_dispari(struct nodo* radice){
	struct nodo* curr = radice;
	
	if(radice != NULL){
		radice->sinistro = elimina_dispari(radice->sinistro);
		radice->destro = elimina_dispari(radice->destro);
	
		if(radice->inf % 2 != 0){
			
			struct nodo* temp = radice;
			
			if(radice->sinistro != NULL) 
				radice = radice->sinistro;
			else 
				radice = radice->destro;
				
			free(temp);
			//radice = elimina_radice(radice);
		}
	}
	return radice;
}



/*
//elimina il nodo dell'albero
struct nodo* elimina_radice(struct nodo* radice){
	
	struct nodo* tmp;
	if(radice!=NULL){
		//Se il nodo da eliminare ha un solo sottoalbero(figlio) o entrambi NULL
		if(radice->destro==NULL || radice->sinistro==NULL){
			tmp=radice;//salva il nodo da eliminare in tmp
			if(radice->destro!=NULL)//se ha figlio destro, sposta il puntatore su quest'ultimo rendendolo il nuovo figlio del padre dell'elemento eliminato
				radice=radice->destro;
			else if(radice->sinistro!=NULL)//se ha un figlio sinistro, sposta il puntatore su quest'ultimo...(come sopra)
				radice=radice->sinistro;
			free(tmp);//elimina l'elemento dopo aver spostato il riferimento del puntatore al nodo figlio
			
		}
		//Se il nodo da eliminare ha due sottoalberi(figli)
		else{//(radice->destro!=NULL && radice->sinistro!=NULL)
			tmp=stacca_minimo(radice->destro, radice);//Trova il minimo tra i massimali (l'estremo superiore: elemento con valore prossimo alla radice, per sostituirla)
			//Un'alternativa è questa:
			//	tmp=stacca_massimo(radice->sinistro, radice);//Trova il massimo tra i minimali (L'estremo inferiore: elemento con valore prossimo alla radice)
			
			radice->inf=tmp->inf;//sovrascrive il nodo da eliminare con quello minimo
			free(tmp);//elimina l'elemento minimo(alla fine, sostituendo l'elemento minimo a quello da eliminare e eliminando quello minimo, si è eliminato il nodo designato)
		}
	}
	return radice;
}


//stacca l'elemento minimo o lo sostituisce all'elemento eliminato(radice->inf=tmp->inf in elimina_radice)
struct nodo* stacca_minimo(struct nodo *radice, struct nodo *padre){
	
	struct nodo* ret;
	if(radice!=NULL){
		if(radice->sinistro!=NULL){//naviga l'albero controllando sempre sui figli sinistri, se trova un nodo senza figlio sinistro allora è minimo
			radice=stacca_minimo(radice->sinistro,radice);//Quando bisogna navigare senza modificare non bisogna assegnare a radice->sinistro perché non si modifica nulla
		}												  //trova l'elemento minimo e lo assegna a "radice"
		else{
			if(padre!=NULL){
				if(padre->sinistro==radice)//se il figlio sinistro di 'padre' è minimo allora il nuovo figlio sinistro di 'padre' sarà il vecchio figlio destro del minimo
					padre->sinistro=radice->destro;
				else if(padre->destro==radice)//l'unica possibilità in cui il figlio destro sia minimo è quando è minimo il primo nodo del sottoalbero destro che stiamo visitando
					padre->destro=radice->destro;
			}
			ret=radice;
		}
	}
	return ret;	
}
*/

//stampa l'albero in ordine
void stampa_in_ordine(struct nodo* radice){
	if(radice!=NULL){
		stampa_in_ordine(radice->sinistro);
		printf(" |%d| ",radice->inf);
		stampa_in_ordine(radice->destro);
		
	}
			
}


