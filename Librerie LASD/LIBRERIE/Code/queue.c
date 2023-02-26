#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


// Inizializza la coda
Queue initQueue() {
    Queue Q = (Queue)malloc(sizeof(struct TQueue));
    Q->A[0] = 0;
    Q->A[QUEUE_MAX+1] = 1;
    return Q;
}


// Ritorna 1 se la coda e' vuota, 0 altrimenti
int emptyQueue(Queue Q){
    return Q->A[0] == 0;
}


// Ritorna 1 se la coda e' piena, 0 altrimenti
int fullQueue(Queue Q){
    return Q->A[0] == Q->A[QUEUE_MAX+1];
}


// Accoda un elemento 'value' dato in ingresso
void enqueue(Queue Q, int value, int *err){
    if (!fullQueue(Q)) {
        Q->A[Q->A[QUEUE_MAX+1]] = value; // Inserisci valore in coda
        if (emptyQueue(Q)) {
            Q->A[0] = 1; // Se e' vuota, sposto la testa in prima posizione
        }
        Q->A[QUEUE_MAX+1] = (Q->A[QUEUE_MAX+1] % (QUEUE_MAX)) + 1;
        *err = 0;
    } else {
        *err = 5;
    }
}


// Toglie un elemento dalla coda
int dequeue(Queue Q, int *err){
    int value = 0;
    if (!emptyQueue(Q)) {
        value = Q->A[Q->A[0]]; // Prendo il valore in 'head' della coda
        Q->A[0] = (Q->A[0] % (QUEUE_MAX)) + 1;
        if (fullQueue(Q)) {
            Q->A[0] = 0;
            Q->A[QUEUE_MAX+1] = 1;
        }
        *err = 0;
    } else {
        *err = 6;
    }
    return value;
}


// Stampa la coda
void printQueueInc(Queue Q, int *err){
    int value;
    if (!emptyQueue(Q)) {
        value = dequeue(Q, err);
        printf("%d ", value);
        printQueueInc(Q, err);
        enqueue(Q, value, err);
    } else {
        *err = 7;
    }
}


// Inserisce valori random nella coda
void randQueue(Queue Q, int dim, int *err){
    int i = 0;
	srand((unsigned int)time(NULL));
    for (i = 0; i < dim; i++){
        enqueue(Q, rand() % 100, err);
    }
}


// Salva la coda in reverse
void reverseQueue(Queue Q, int *err){
    int value;
    if (!emptyQueue(Q)) {
        value = dequeue(Q, err);
        reverseQueue(Q, err);
        enqueue(Q, value, err);
    } else {
        *err = 8;
    }
}


// Stampa la coda
void printQueue(Queue Q, int *err){
    printQueueInc(Q, err); // Stampa la coda
    reverseQueue(Q, err); // Riordina la coda prima di uscire
}