#include <stdio.h>
#include <stdlib.h>
#define MAX 20
int ArraySize, HeapSize, tot;

int left(int i) { return 2*i+1;}

int right(int i) { return 2*i+2;}

int p(int i) {return (i-1)/2;}

void swap(int A[MAX], int i, int j){
	int tmp = A[i];
	A[i] = A[j]; 
	A[j] = tmp;
}
	
//Prototipi
void Heapify(int A[MAX], int i);
void BuildHeap(int A[MAX]);
void HeapSort(int A[MAX]);

main(){
	int A[MAX], k;
	printf("\n Quanti elementi deve contenere l'array: ");
	scanf("%d",&tot);
	
	while (tot>MAX) { 
		printf("\n max 20 elementi: "); scanf("%d",&tot);
	}
	for (k=0;k<tot;k++) {
		printf("\nInserire il %d° elemento: ",k+1);
		scanf("%d",&A[k]); 
	}
	HeapSize=ArraySize=tot;
	HeapSort(A);
	printf("\n Array Ordinato:");
	for (k=0;k<tot;k++)
		printf(" %d",A[k]);
}



void Heapify(int A[MAX], int i)
{
	int l,r,largest; //largest contiene la posizione dell'elemento massimo tra il padre e i suoi figli
	l = left(i);
	r = right(i);
	//Controlli
	if (l < HeapSize && A[l] > A[i])
		largest = l; 
	else largest = i;
	if (r < HeapSize && A[r] > A[largest])
		largest = r;
		
	//Sostituzione e di conseguenza chiamata ricorsiva
	if (largest != i) {
		swap(A, i, largest);
		Heapify(A, largest); //si riapplica heapify al valore appena cambiato così a cascata
	}
}


//COSTRUISCE L'ALBERO HEAP A PARTIRE DA UN ALBERO NON ORDINATO
void BuildHeap(int A[MAX])
{
	int i;
	HeapSize = ArraySize;
	for (i=ArraySize/2; i>=0; i--) //partiamo dai padri delle foglie per arrivare alla radice
		Heapify(A, i);
}

void HeapSort(int A[MAX])
{
	int i;
	BuildHeap(A);//Rende l'albero un heap
	
	//Questo parte di codice permette di estrapolare l'elemento massimo in cima e ridistribuirlo
	//in coda, fondamentalmente serve per cambiare il tipo di ordinamento da decrescente a crescente
	for (i=ArraySize-1; i>=1; i--) {
		swap(A, 0, i);//Swappa il valore massimo nella posizione i
		ArraySize--;//Decrementa HeapSize perché l'ultimo elemento appena swappato è ordinato
		Heapify(A, 0);//Riordina l'albero rendendolo di nuovo un heap
	}
}
