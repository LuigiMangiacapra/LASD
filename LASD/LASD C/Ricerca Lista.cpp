/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L, raddoppi tutti gli elementi dispari 
della lista
*/

/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L e un intero el, rimuova una 
ricorrenza di el dalla lista (se ne esiste una)
*/

/*
Scrivere in linguaggio C una funzione ricorsiva che 
preso in input L, la modifichi in modo tale che ogni 
numero dispari sia seguito dal suo successore pari.
*/


#include <stdio.h>
#include <malloc.h>

struct elem *crea_lista(int n, struct elem *testa);
void visualizza_lista(struct elem *lista);
int ricerca(struct elem *l, int k);
struct elem * elimina(struct elem *l, int k);
struct elem* inserimento_disp(struct elem*l);
struct elem* max_elem(struct elem*l, struct elem*max);

struct elem{
	int inf;
	struct elem *next;
};

int main(){
	int k=0,r=0,m,n;
	struct elem *lista;
	struct elem *max;
	struct elem *testa = NULL;
	do{
		printf("\nChe cosa vuoi fare con la lista?\n\n");
		printf("0-crea, 1-ricerca, 2-inserimento_disp, 3-eliminazione, 4-stampa, 5-trova_massimo, 6-exit\n");
		scanf("%d",&m);
		switch(m){
			case 0:
				printf("Specificare numero di elementi\n");
				scanf("%d", &n);
				lista=crea_lista(n, testa); 
				break;
			case 1:
				printf("Digita elemento da ricercare:\n");
				scanf("%d",&k);
				r=ricerca(lista, k);
				if(r==1)
					printf("elemento trovato\n");
				else if(r==0)
					printf("elemento non trovato\n");
				break;
			case 2:
				lista=inserimento_disp(lista);
				break;
			case 3:
				printf("Digita elemento da eliminare:\n");
				scanf("%d",&k);
				lista=elimina(lista, k);
				break;
			case 4:
				printf("\nlista ---> ");
				visualizza_lista(lista);
				
				printf("NULL\n\n"); 
				break;
			case 5:
				max = lista;
				max=max_elem(lista->next, max);
				printf("L'elemento massimo e' %d",max->inf);
			
		}
	}
	while(m==0 || m==1 || m==2 || m==3 || m==4 || m==5);
	
	
	
	
}


struct elem *crea_lista(int n, struct elem *testa){
	
	if(n != 0){
		
		testa=(struct elem *)malloc(sizeof(struct elem));
		printf("inserire primo elemento\n");
		scanf("%d",&testa->inf);
		testa->next = NULL; //da inserire per dare un next iniziale
		
		n = n - 1;
		testa->next = crea_lista(n, testa->next);
	}
	return(testa);
}



void visualizza_lista(struct elem *p) {
	
	if(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
		visualizza_lista(p);
	}
	
} 


int ricerca(struct elem *l, int k){
	
	int r=0;
	if(l==NULL) //se la lista è vuota o si è arrivati all fine della lista allora non è stato trovato alcun elemento
		r=0;
	else{
		if(l->inf==k)//appena trova l'elemento non fa più chiamate ricorsive, ormai inutili
			r=1;
		else
			r=ricerca(l->next,k);
		
	}
	return r;
}

//elimina da una lista non ordinata
struct elem * elimina(struct elem *l, int k){
	struct elem* tmp;
	if(l != NULL){
		//Se l'elemento non è stato trovato effettua la chiamata ricorsiva sull'elemento successivo
		if(l->inf != k)
			l->next = elimina(l->next,k);
		else{
			tmp = l;
			l = l->next;//passa all'elemento successivo e collega il nodo precedente a l ad l->next in modo che il nuovo valore successivo sia l->next poiché l è da eliminare
			free(tmp);
		}
	}
	return l;
}

//funzione che inserisce per ogni elemento dispari il suo successore pari(es° input: 1->2->4->6  output: 1->2->3->4->5->6->7)
struct elem* inserimento_disp(struct elem*l){
	struct elem* tmp=l;
	
	if(l!=NULL){
		
		l->next=inserimento_disp(l->next);
		
	  	if(l->inf%2!=0){
	  		//CREAZIONE SINGOLO NODO
			tmp=(struct elem*)malloc(sizeof(struct elem)); //crea uno spazio in memoria
			tmp->inf=(l->inf)+1; //crea il valore pari successivo al valore dispari trovato
			tmp->next=l->next;	//prima decidere il next dell'elemento da inserire e poi il next dell'elemento precedente
			//AGGANCIO DEL NODO APPENA CREATO
			l->next=tmp;
		
		}
	}
	return l;
}


//funzione che restituisce l'elemento con valore massimo
struct elem* max_elem(struct elem*l, struct elem*max){
	struct elem* tmp;
	
	if(l != NULL){
		
		if(max->inf < l->inf){
			max = l;//elemento puntato da max
			//max->inf = l->inf;//max conserva l'elemento
		}
		max = max_elem(l->next, max);
	}
	return max;
}



