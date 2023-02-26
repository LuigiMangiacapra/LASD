
#include <stdio.h>
#include <malloc.h>

struct el
{
	struct el *prev;
	int inf;
	struct el *next;
};

struct el *crea_lista();
struct el *inserisci(struct el*,int);
void visualizza_lista(struct el *lista);
struct el* inserisci_testa(struct el* L, int valore);
struct el* alterna_liste(struct el* L1, struct el* L2);
struct el* elimina_negativi(struct el* L2);

int main(){
	int liste;
	struct el *lista[liste];
	int valore,valore2;
	int i=0;
	
	printf("Quante liste vuoi creare?\n");
	scanf("%d",&liste);
	while(1){
		lista[i]=crea_lista();
		visualizza_lista(lista[i]);
		i++;
		if(i==liste){
			break;
		}
	}
	
	lista[1]=alterna_liste(lista[0], lista[1]);
	elimina_negativi(lista[1]);
	visualizza_lista(lista[1]);
}


struct el *crea_lista() {
	struct el *p, *punt;
	int i, n;
	printf("\n Specificare il numero di elementi... ");
	scanf("%d", &n);
	if(n==0) 
		p = NULL; 
	else {
		/* creazione primo elemento */
		p = (struct el *)malloc(sizeof(struct el));
		printf("\nInserisci il primo valore: ");
		scanf("%d", &p->inf);
		punt = p; p-> prev=NULL;
		for(i=2; i<=n; i++)
		{	
			punt->next = (struct el *)malloc(sizeof(struct el));
			punt->next->prev=punt;
			punt = punt->next;
			printf("\nInserisci il %d elemento: ", i);
			scanf("%d", &punt->inf);
		} // chiudo il for
		punt->next = NULL; // marcatore fine lista
	} // chiudo l'if-else
	return(p);
} // chiudo la funzione




struct el *inserisci(struct el *p, int valore)
{ 
	struct el *nuovo=NULL;
	struct el *testa;
	if (p==NULL) {
		p=(struct el *)malloc(sizeof(struct el));
		p->inf=valore; p->prev=NULL; testa=p; 
	}
	else {
		testa=p;
		while (p->next!= NULL) 
			p=p->next;
		nuovo=(struct el *)malloc(sizeof(struct el));
		nuovo->prev=p;
		nuovo->inf=valore;
		nuovo->next = NULL; 
	}
	p->next=nuovo; 
	return testa;
}

void visualizza_lista(struct el *p) {
	printf("\nlista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 


//inserimento in testa
struct el* inserisci_testa(struct el* L, int valore){
	struct el*punt;
	if(L==NULL){
		L=(struct el*)malloc(sizeof(struct el*));
		L->inf=valore;
		L->prev=NULL;
		L->next=NULL;
		
	}
	else{
		punt=L;
		punt=(struct el*)malloc(sizeof(struct el*));
		punt->prev=NULL;
		punt->inf=valore;
		punt->next=L;
		punt->next->prev=punt;
		L=punt;
		
	}
	return L;
}



struct el* alterna_liste(struct el* L1, struct el* L2){
	
	struct el* temp1=L1;
	struct el* temp2=L2;
	struct el* newnode;
	
	if(temp1!=NULL && temp2!=NULL){
		
		temp2->next=alterna_liste(L1->next, L2->next);
		
		//Creazione singolo nodo
		newnode=(struct el*)malloc(sizeof(struct el*));//CREA LO SPAZIO DI MEMORIA PER IL NODO
		newnode->inf=temp1->inf;//INSERISCE IL VALORE DELLA LISTA1
		newnode->next=temp2->next;//IMPORTANTE! IL SUCCESSIVO E' IL NODO SCORSO PRECEDENTEMENTE
		newnode->prev=temp2;
		
		//Aggancia ad ogni elemento della lista 2 il nodo creato precedentemente
		temp2->next=newnode;
		temp2->next->prev=temp2;
		
		
		
		
	}
	
	return L2;
}


struct el* elimina_negativi(struct el* L2){
	
	struct el* temp2=L2;
	struct el* temp;
	
	if(temp2!=NULL){
		
		temp2->next=elimina_negativi(L2->next);
	
		if(temp2->inf < 0){
			
			if(temp2==L2){
				L2=L2->next;
				L2->next->prev=temp2->prev;
				free(temp2);
				temp2=NULL;
				
			}
			else{
				temp=temp2;
				temp2=temp2->next;
				temp2->next->prev=temp2->prev;
				free(temp);
				temp=NULL;
			}	
		}
		 
	}
	
	return L2;
}


