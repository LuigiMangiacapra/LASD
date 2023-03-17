/*
Realizzare un menù a scelta multipla che permetta:
1. Creare un ABR di interi (senza valori uguali e tutti positivi);
2. Aggiungere un nodo ad un ABR;
3. Cercare un valore nell ABR;
4. Cercare il minimo nell ABR;
5. Stampare gli elementi dell ABR con una visita in ordine;


Aggiungere al menù precedente una scelta che, data 
una lista di interi non circolare e singolarmente puntata permetta, 
6.1 di rimuovere dalla lista i numeri dispari e inserirli 
opportunamente nell ABR
6.2 di stampare la lista e l albero modificati

*/


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//Struttura albero
struct nodo{
	int inf;
	struct nodo *sinistro, *destro;	
};

//Struttura lista
struct elem{
	int inf;
	struct elem *next;
};


int vuoto(struct nodo* radice){
	if(radice) return 0;
	return 1;
}

int radice(struct nodo* radice, struct nodo *val){
	int ok=0;
	if(!vuoto(radice)){
		val->inf=radice->inf;
		ok=1;
	}
	return ok;
}

struct nodo* sinistro(struct nodo* radice){
	struct nodo*sinistro=NULL;
	if(!vuoto(radice)){
		sinistro=radice->sinistro;
	}
	return sinistro;
}

struct nodo* destro(struct nodo* radice){
	struct nodo*destro=NULL;
	if(!vuoto(radice)){
		destro=radice->sinistro;
	}
	return destro;
}

struct nodo* crea_nodo(struct nodo* sinistro, struct nodo* destro, int elem){
	struct nodo* padre;
	padre=(struct nodo*)malloc(sizeof(struct nodo));
	if(padre != NULL){
		padre->inf=elem;
		padre->destro=destro;
		padre->sinistro=sinistro;
	}
	return padre;
}


//PROTOTIPI
int riconosci_ABR(struct nodo* radice);
struct nodo* inserisci(struct nodo* radice, int k);
struct nodo* ricerca(struct nodo* radice, int k);
int trova_minimo(struct nodo* radice);
void stampa_in_ordine(struct nodo*radice);
void cancella_albero(struct nodo* radice);
void visualizza_lista(struct elem *p);
struct elem* sposta_dispari(struct nodo* radice,struct elem *testa);
struct elem *crea_lista();
struct nodo* elimina(struct nodo* radice, int k);
struct nodo* elimina_radice(struct nodo* radice);
struct nodo* stacca_minimo(struct nodo*radice, struct nodo*padre);


int main(){
	struct nodo* radice=NULL;//Mettere sempre NULL
	int n,k=0,count=0,scelta,cerca;
	struct elem* p=NULL,*testa=NULL;
	do{
		printf("\nScegli l'operazione da svolgere:\n");
		printf("1-Crea_albero, 2-Inserimento_nodo, 3-Ricerca, 4-Ricerca_minimo, 5-stampa_in_ordine, 6-cancella_albero,\n7-sposta dispari da lista ad albero e eliminarli dalla lista, 8-stampa_lista, 9-crea_lista, 10-cancella elemento da albero, 11-esci\n");
		scanf("%d",&scelta);
		switch(scelta){
			case 1:
				printf("Quanti elementi vuoi inserire?\n");
				scanf("%d",&n);
	
				while(n != 0){
					count++;
					printf("Inserici elemento %d:\n",count);
					scanf("%d",&k);
					radice=inserisci(radice, k);
					n--;
				}
				break;
			case 2:
				printf("Inserici elemento:\n",count);
				scanf("%d",&k);
				radice=inserisci(radice, k);
				break;
			case 3:
				printf("Digita cosa ricercare:\n");
				scanf("%d",&cerca);
				if(ricerca(radice, cerca)==NULL)
					printf("Elemento non presente\n");
				else
					printf("L'elemento %d e' stato trovato\n",ricerca(radice, cerca)->inf);
				
				break;
			case 4:
				printf("L'elemento minimo e' %d", trova_minimo(radice));
				break;
			case 5:
				stampa_in_ordine(radice);
				break;
			case 6:
				cancella_albero(radice);
				printf("Albero cancellato\n");
				break;
			case 7:
				sposta_dispari(radice, testa);
				break;
			case 8:
				visualizza_lista(testa);
				break;
			case 9:
				testa=crea_lista(); 
				break;
			case 10:
				printf("Inserisci elemento da eliminare\n");
				scanf("%d",&k);
				radice=elimina(radice, k);
		}
	}
	while(scelta==1 || scelta==2 || scelta==3 || scelta==4 || scelta==5 || scelta==6 || scelta==7 || scelta==8 || scelta==9 || scelta==10);
}


//inserisce nodo nell'albero 
struct nodo* inserisci(struct nodo* radice, int k){
	
	if(radice==NULL)
		radice=crea_nodo(NULL, NULL,k);//Ricordare sempre il tipo di ritorno di una funzione che modifica la struttura
	else{
		if(radice->inf<k)
			radice->destro=inserisci(radice->destro,k);
		else if(radice->inf>k)
			radice->sinistro=inserisci(radice->sinistro,k);
	}
	return radice;
}


//ricerca un elemento k nell'albero
struct nodo* ricerca(struct nodo* radice, int k){
	//Si evita di inserire come caso base radice==NULL perché nel caso, non fa nulla
	if(radice!=NULL){
		if(radice->inf==k)
			return radice;
		else{
			if(radice->inf<k)//se il nodo corrente ha un elemento minore di k cerca a destra
				radice=ricerca(radice->destro, k);
			else if(radice->inf>k)//altrimenti a sinistra
				radice=ricerca(radice->sinistro, k);
		}
	}
	return radice;
}


//trova elemento minimo nell'albero
int trova_minimo(struct nodo* radice){
	int min;
	if(radice!=NULL){
		min=trova_minimo(radice->sinistro);//effettua chiamate ricorsive fino ad arrivare alla prima foglia del sottoalbero sinistra(cioè la foglia con elemento minimo)
		if(radice->sinistro==NULL)//se non ha un figlio sinistro allora abbiamo raggiunto il nodo con elemento minimo
			min=radice->inf;//salviamo il valore del nodo in min
	}
	return min;
}


//stampa l'albero in ordine
void stampa_in_ordine(struct nodo* radice){
	if(radice!=NULL){
		stampa_in_ordine(radice->sinistro);
		printf(" |%d| ",radice->inf);
		stampa_in_ordine(radice->destro);
		
	}
			
}

/*
//stampa l'albero in pre-ordine
void stampa_in_pre-ordine(struct nodo* radice){
	if(radice!=NULL){
		printf(" |%d| ",radice->inf);
		stampa_in_ordine(radice->sinistro);
		stampa_in_ordine(radice->destro);
		
	}
			
}

//stampa l'albero in post-ordine
void stampa_in_post-ordine(struct nodo* radice){
	if(radice!=NULL){
		stampa_in_ordine(radice->sinistro);
		stampa_in_ordine(radice->destro);
		printf(" |%d| ",radice->inf);
		
	}
			
}

*/

//cancella ogni elemento dell'albero
void cancella_albero(struct nodo* radice){
	if(radice!=NULL){
		cancella_albero(radice->sinistro);
		cancella_albero(radice->destro);
		free(radice);
	}
}

//Come viene cancellato un albero:
/*
- Vengono cancellati prima le foglie poi i padri delle foglie cancellate e così via.
  Nello specifico vengono cancellati tutti quei nodi che non hanno figli in quanto
  le due chiamate ricorsive sono state chiamate restituendo NULL e quindi rimane la free
  da effettuare
*/


//stampa la lista
void visualizza_lista(struct elem *p) {
	printf("\nlista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 

//crea la lista
struct elem *crea_lista(){
	struct elem *testa, *punt;
	int i, n;
	printf("Specificare numero di elementi\n");
	scanf("%d", &n);
	
	if(n==0){
		testa=NULL;
	}
	else{
		testa=(struct elem *)malloc(sizeof(struct elem));
		printf("inserire primo elemento\n");
		scanf("%d",&testa->inf);
		punt=testa;
		for(i=2;i<=n;i++){
			punt->next=(struct elem *)malloc(sizeof(struct elem));
			punt=punt->next;
			printf("inserire il %d elemento:\n",i);
			scanf("%d",&punt->inf);
		
		}
		punt->next=NULL;
	
	}
	return(testa);
}


//inserisce nell'albero ogni elemento dispari della lista eliminandolo dalla lista
struct elem* sposta_dispari(struct nodo* radice,struct elem *testa){
	struct elem* tmp;
	
	if(testa!=NULL){
		
		testa->next=sposta_dispari(radice,testa->next);//poiché l'albero viene giù modificato tramite la funzione inserisci, dobbiamo ciclare sulla lista
		
		if(testa->inf%2!=0){
			radice=inserisci(radice, testa->inf);//Modifica direttamente l'albero
			
			//Elimina dalla lista l'elemento appena inserito nell'albero
			tmp=testa;
			testa=testa->next;
			free(tmp);
		}
	}
	
	return testa;
		
}



//Elimina elemento dall'albero
struct nodo* elimina(struct nodo* radice, int k){
	if(radice!=NULL){//se l'albero non è vuoto o si è arrivati ad un nodo NULL (figlio di una foglia)
		//cerca nel sottoalbero destro
		if(k>radice->inf)
			radice->destro=elimina(radice->destro, k);
		//cerca nel sottoalbero sinistro
		else if(k<radice->inf){
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
			/*Un'alternativa è questa:
				tmp=stacca_massimo(radice->sinistro, radice);//Trova il massimo tra i minimali (L'estremo inferiore: elemento con valore prossimo alla radice)
			*/
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
