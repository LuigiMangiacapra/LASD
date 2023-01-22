/*
-Si impelementi un gioco tra due giocatori (Tom e Jerry) realizzato
su alberi binari di ricerca di interi nel modo seguente:
-Tom e Jerry hanno a disposizione un albero binario di ricerca di
interi a testa.
-I due muovono a turni. Inizia Jerry a muovere.
-Scopo del gioco per TOM: acciuffare JERRY. Il che si concretizza
per TOM nel trovarsi in un nodo il cui valore è identico a quello in
cui si trova Jerry.

*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define RANGE 20
#define TOT 20

struct nodo{
	int inf;
	struct nodo* sinistro;
	struct nodo* destro;
};


struct nodo* crea_nodo(struct nodo* sinistro, struct nodo* destro, int elem){
	struct nodo* padre;
	padre=(struct nodo*)malloc(sizeof(struct nodo));
	if(padre){
		padre->inf=elem;
		padre->destro=destro;
		padre->sinistro=sinistro;
	}
	return padre;
}

void stampa_in_ordine(struct nodo* radice);
struct nodo* simula_gioco(struct nodo* radice1, struct nodo* radice2);
struct nodo* elimina(struct nodo* radice, int k);
struct nodo* elimina_radice(struct nodo* radice);
struct nodo* stacca_minimo(struct nodo *radice, struct nodo*padre);
struct nodo* inserisci(struct nodo* radice, int k);
struct nodo* ricerca(struct nodo* radice, int k);

int main(){
	struct nodo* radice1=NULL,*radice2=NULL;
	int n,k,count=0,scelta;
	do{
		printf("\nChe operazione vuoi svolgere?\n");
		printf("1-Riempimento albero_1, 2-riempimento albero_2, 3-Simulare il gioco, 4-Stampare in ordine gli alberi, 5-uscire\n");
		scanf("%d",&scelta);
		switch(scelta){
			case 1:
				
				printf("Quanti elementi vuoi inserire nell'albero_1?\n",count);
				scanf("%d",&n);
				if(n<=TOT){
					while(n){
						count++;
						printf("Inserisci elemento %d\n",count);
						scanf("%d",&k);
						if(k<=RANGE && k>=1){
							radice1=inserisci(radice1, k);
						}
						else{
							printf("Inserimento non possibile, oltre il range 1-%d",RANGE);
							break;
						}
						n--;
						
					}
				}
				else{
					printf("Troppi elementi, max elementi = %d\n",TOT);
					break;
				}
				break;
			case 2:
				printf("Quanti elementi vuoi inserire nell'albero_2?\n",count);
				scanf("%d",&n);
				if(n<=TOT){
					while(n){
						count++;
						printf("Inserisci elemento %d\n",count);
						scanf("%d",&k);
						if(k<=RANGE && k>=1){
							radice2=inserisci(radice2, k);
						}
						else{
							printf("Inserimento non possibile, oltre il range 1-%d",RANGE);
							break;
						}
						n--;
					}
				}
				else{
					printf("Troppi elementi, max elementi = %d",TOT);
					break;
				}
				break;
			case 3:
				radice2=simula_gioco(radice1, radice2);
				break;
			case 4:
				stampa_in_ordine(radice1);
				printf("\n");
				stampa_in_ordine(radice2);
				
		}
	}
	while(scelta==1 || scelta==2 || scelta==3 || scelta==4);
	

}


void stampa_in_ordine(struct nodo* radice){
	if(radice!=NULL){
		stampa_in_ordine(radice->sinistro);
		printf(" |%d| ",radice->inf);
		stampa_in_ordine(radice->destro);
		
	}
		
	
}


struct nodo* inserisci(struct nodo* radice, int k){
	
	if(radice==NULL)
		radice=crea_nodo(NULL, NULL,k);//Ricordare sempre il tipo di ritorno di una funzione
	else{
		if(radice->inf<k)
			radice->destro=inserisci(radice->destro,k);
		else if(radice->inf>k)
			radice->sinistro=inserisci(radice->sinistro,k);
	}
	return radice;
}


struct nodo* ricerca(struct nodo* radice, int k){
	if(radice!=NULL){
		if(radice->inf==k)
			return radice;
		else{
			if(radice->inf<k)
				radice=ricerca(radice->destro, k);
			else if(radice->inf>k)
				radice=ricerca(radice->sinistro, k);
		}
	}
	return radice;
}


struct nodo* simula_gioco(struct nodo* radice1, struct nodo* radice2){
	struct nodo *tmp1=radice1, *tmp2=radice2;
	if((tmp1->sinistro!=NULL || tmp1->destro!=NULL) || (tmp2->sinistro!=NULL || tmp2->destro!=NULL)){
		if(tmp2->inf>tmp1->inf){
			tmp2->destro=simula_gioco(tmp1, tmp2->destro);
		}
		else if(tmp1->inf>tmp2->inf){
			tmp1->destro=simula_gioco(tmp1->sinistro, tmp2);
		}
		else if(tmp1->inf==tmp2->inf){
			tmp2=elimina(tmp2, tmp2->inf);
			return tmp2;
		}
	}
	else{
		if(tmp1->inf != tmp2->inf){
			if(tmp2->inf!=ricerca(tmp1,tmp2->inf)->inf){
				tmp1=inserisci(tmp1, tmp2->inf);
				tmp1=radice1;
				tmp2=radice2;
				
			}
		}
	}
	return tmp2;
}



struct nodo* simula_gioco(struct nodo* tom, struct nodo* jerry){
	
	if()
	
	
	
}

//Elimina elemento

struct nodo* elimina(struct nodo* radice, int k){
	if(radice!=NULL){
		if(k>radice->inf)
			radice->destro=elimina(radice->destro, k);
		else if(k<radice->inf)
			radice->sinistro=elimina(radice->sinistro, k);
		else
			radice=elimina_radice(radice);
	}
	return radice;
}


struct nodo* elimina_radice(struct nodo* radice){
	struct nodo* tmp;
	if(radice!=NULL){
		//Se il nodo da eliminare ha un solo sottoalbero
		if(radice->destro==NULL || radice->sinistro==NULL){
			tmp=radice;
			if(radice->destro!=NULL)
				radice=radice->destro;
			else if(radice->sinistro!=NULL)
				radice=radice->sinistro;
			free(tmp);
			
		}
		//Se il nodo da eliminare ha due sottoalberi
		else{
			tmp=stacca_minimo(radice->destro, radice);//Trova il minimo tra i massimali (l'estremo superiore: elemento con valore prossimo alla radice)
			/*Un'alternativa è questa:
				tmp=stacca_massimo(radice->sinistro, radice);//Trova il massimo tra i minimali (L'estremo inferiore: elemento con valore prossimo alla radice)
			*/
			radice->inf=tmp->inf;
			free(tmp);
		}
	}
	return radice;
}


struct nodo* stacca_minimo(struct nodo *radice, struct nodo*padre){
	struct nodo* ret;
	if(radice!=NULL){
		if(radice->sinistro!=NULL){
			radice=stacca_minimo(radice->sinistro,radice);//Quando bisogna navigare senza modificare non bisogna assegnare a radice->sinistro perché non si modifica nulla
		}												  //trova l'elemento minimo e lo assegna a "radice"
		else{
			if(padre!=NULL){
				if(padre->sinistro==radice)
					padre->sinistro=radice->destro;
				else if(padre->destro==radice)
					padre->destro=radice->destro;
			}
			ret=radice;
		}
	}
	return ret;	
}
