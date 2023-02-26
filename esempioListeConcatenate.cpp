//Lezione del 23/05/2012. Esempio Liste Concatenate.
#include <iostream>
#include <cstdlib>
//Il seguente define permette di specificare il tipo di dati
//presente nel campo info dell'elemento della lista concatenata
#define TIPO_INFO int
//Ad esempio se vogliamo che il tipo del campo info sia 'float':
//#define TIPO_INFO float

using namespace std;

//Struttura per rappresentare un elemento di una lista concatenata;
struct elem {
	
	
	TIPO_INFO info;	//Campo in cui mantenere le informazioni
			//Il tipo int e' un esempio.
			//Si possono considerare tipi diversi (float, char, char *, e cosi' via)
			//E' possibile considerare piu' campi di tipo diverso.
	struct elem *next; 	
};


//******DICHIARAZIONE FUNZIONI *************

//Funzione x creare un nuovo elemento della lista.
//Restituisce l'indirizzo di memoria del nuovo elemento creato.
struct elem *newElem(TIPO_INFO);

//Funzione x aggiungere un elemento in testa alla lista.
//Restituisce il top della lista aggiornata.
struct elem *addHeadList(struct elem *,TIPO_INFO);

//Funzione x aggiungere un elemento alla fine della lista.
//Restituisce il top della lista aggiornata.
struct elem *addEndList(struct elem *,TIPO_INFO);

//Funzione x eliminare un elemento dalla lista.
//Restituisce il top della lista aggiornata.
//Versione ricorsiva
struct elem *delListElem(struct elem *,TIPO_INFO);

//Funzione x inserire un elemento gia' creato in una lista
//ordinata, lasciando la lista ancora ordinata.
//Restituisce il top della lista aggiornata.
//VERSIONE ITERATIVA
struct elem *insertInSortedList(struct elem *,struct elem *);

//Funzione x inserire un elemento gia' creato in una lista
//ordinata, lasciando la lista ancora ordinata.
//Restituisce il top della lista aggiornata.
//VERSIONE RICORSIVIVA
struct elem *insertInSortedListRicorsiva(struct elem *,struct elem *);

//Funzione x ordinare una lista.
//Restituisce il top della lista ordinata.
//VERSIONE RICORSIVIVA
struct elem *sortListRicorsiva(struct elem *);

//Funzione x cercare un elemento in una lista.
//Restituisce l'indirizzo di memoria dell'elemento cercato.
//VERSIONE RICORSIVIVA
struct elem *findInListRicorsiva(struct elem *, TIPO_INFO);

int main () {
	int n,i;
	TIPO_INFO a;
	struct elem *top=NULL,*x;
	
	//ERRORE: top.info, top->info
	top=(struct elem *)malloc(sizeof(struct elem));
	//ERRORE: top.info
	//CORRETTO: top->info, oppure (*top).info	
	cout << "Quanti elementi vuoi inserire? ";
	cin >> n;
	for (i=0;i< n; ++i){
		cout << "Elemento " << i+1 <<": ";
		cin >> a;
		//x=newElem(a);
		//top=insertInSortedList(top,x);
		//top=insertInSortedListRicorsiva(top,x);
		top=addHeadList(top,a);		
	}
	top=sortListRicorsiva(top);
	i=0;
	while (top!=NULL) {
		++i;
		cout<< "Elem["<<i<<"]:"<< top->info <<endl;
		top=top->next;
	}	 

return 0;
}
//Funzione x confrontare due elementi di una lista.
//Restituisce -1 se il primo elemento e' minore del secondo,
//1 se il secondo elemento e' minore del primo, 0 altrimenti
int compareListElem(struct elem *a,struct elem *b) {
	int result=0;
	if (a->info < b->info) result=-1;
	else if (a->info > b->info) result=1;
	return result;
} 


//Funzione x creare un nuovo elemento della lista.
//Restituisce l'indirizzo di memoria del nuovo elemento creato.
struct elem *newElem(TIPO_INFO x){
	struct elem *pnt=NULL;
	pnt=(struct elem *)malloc(sizeof(struct elem));
	pnt->info=x;
	pnt->next=NULL;
	return pnt;
}

//Funzione x aggiungere un elemento in testa alla lista.
//Restituisce il top della lista aggiornata.
struct elem *addHeadList(struct elem *top,TIPO_INFO x){
	struct elem *pnt=newElem(x); //Creo un nuovo elemento
	pnt->next=top;
	return pnt;
}

//Funzione x aggiungere un elemento alla fine della lista.
//Restituisce il top della lista aggiornata.
struct elem *addEndList(struct elem *top,TIPO_INFO x){
	struct elem *pnt=newElem(x); //Creo un nuovo elemento
	struct elem *currPnt;

	if (top!=NULL) {//Se la lista non e' vuota	
		currPnt=top;
		while (currPnt->next!=NULL) //Scorro la lista fino ad arrivare all'ultimo elemento
			currPnt=currPnt->next;
		currPnt->next=pnt; //Aggiungo il nuovo elemento alla fine della lista
	}
	else top=pnt; //Se la lista e' vuota, aggiungo il nuovo elemento come top della lista
	return top;
}
//Funzione x eliminare un elemento dalla lista.
//Restituisce il top della lista aggiornata.
//Versione ricorsiva
struct elem *delListElem(struct elem *top,TIPO_INFO a){
	struct elem *tmp;
	if (top!=NULL) {
		if (top->info==a){
			tmp=top;
			top=top->next;
			tmp->next=NULL;
			free(tmp);
		} 
		else
			top->next=delListElem(top->next,a);
		  
	}
	return top;
	
}

//Funzione x inserire un elemento gia' creato in una lista
//ordinata, lasciando la lista ancora ordinata.
//Restituisce il top della lista aggiornata.
//VERSIONE ITERATIVA
struct elem *insertInSortedList(struct elem *top,struct elem *x){
	struct elem *curr;
	struct elem **prevCurr; //puntatore a puntatore
	int ancora=1;
	x->next=NULL;
	
	if (top==NULL) {
		top=x;
	}
	else {
		curr=top;	
		prevCurr=&top;
		while (curr!=NULL && ancora) {
			
			if ( compareListElem(curr,x)==-1) {	
				prevCurr=&(curr->next);
				curr=curr->next;
			}
			else ancora=0;
				
		}
		*prevCurr=x;
		x->next=curr;
	}

return top;
	
}



//Funzione x inserire un elemento gia' creato in una lista
//ordinata, lasciando la lista ancora ordinata.
//Restituisce il top della lista aggiornata.
//VERSIONE RICORSIVIVA
struct elem *insertInSortedListRicorsiva(struct elem *top,struct elem *x){
	x->next=NULL;	
	if (top==NULL)
		top=x;
	else {
		if (compareListElem(top,x)==-1) {
			top->next=insertInSortedListRicorsiva(top->next,x);
		}
		else{
			x->next=top;
			top=x;
		}
		
	}
return top;

}
//Funzione x ordinare una lista.
//Restituisce il top della lista ordinata.
//VERSIONE RICORSIVIVA
struct elem *sortListRicorsiva(struct elem *top){
	struct elem *tmp;
	if (top!=NULL) {
		tmp=sortListRicorsiva(top->next);
		top=insertInSortedListRicorsiva(tmp,top);
	}
return top;	
}

//Funzione x cercare un elemento in una lista.
//Restituisce l'indirizzo di memoria dell'elemento cercato.
//VERSIONE RICORSIVIVA
struct elem *findInListRicorsiva(struct elem *top, TIPO_INFO a){
	struct elem *trovato=top;
	if (top!=NULL && a!=top->info)
		trovato= findInListRicorsiva(top->next,a); 
return trovato;	
}

