#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"


// Inizializza lo Stack
Stack initStack() {
    Stack S = (Stack)malloc(sizeof(struct TStack));
	S->A[0] = 0;
    return S;
}


// Ritorna 1 se lo Stack e' vuoto, 0 altrimenti
int emptyStack(Stack S){
	return S->A[0] == 0;
}


// Ritorna 1 se lo Stack e' pieno, 0 altrimenti
int fullStack(Stack S){
	return S->A[0] == STACK_MAX;
}


// Inserisce il dato 'value' nello Stack, se non e' pieno
void push(Stack S, int value, int *err){
	if(!fullStack(S)){
		S->A[0]++;
		S->A[S->A[0]] = value;
		*err = 0;
	} else {
		*err = 1;
	}
}


// Estrae dallo Stack un elemento e lo ritorna
int pop(Stack S, int *err){
	if(!emptyStack(S)){
		S->A[0]--;
		*err = 0;
		return S->A[S->A[0]+1];
	} else {
		*err = 2;
		return 0;
	}
}


// Dato uno Stack S, attraversera' tutto lo Stack inserendo
// in un altro Stack dato in ingresso 'tmp' tutti gli
// elementi nell'ordine inverso
void reverseStack(Stack S, Stack tmp, int *err){
	int value;
	if(!emptyStack(S)){
		value = pop(S, err);
		push(tmp, value, err);
		reverseStack(S, tmp, err);
		push(S, value, err);
	}
}


// Stampa lo Stack dato in ingresso
void printStack(Stack S, int *err){
	int value;
	if(!emptyStack(S)){
		value = pop(S, err);
		printf("%d ", value);
		printStack(S, err);
		push(S, value, err);
	}
}

// Crea uno stack random
void randomStack(Stack S, int n, int *err) {
    srand((unsigned int)time(NULL));
    int i = 0;
    for (i = 0; i < n; i++) {
        push(S, rand() % 40, err);
    }
}
