#ifndef Library_queue_h
#define Library_queue_h
#define QUEUE_MAX 128

struct TQueue {
    int A[QUEUE_MAX+2];
};

typedef struct TQueue* Queue;

// Inizializza una nuova coda e ritorna un puntatore
// ad una struct di tipo Queue
Queue initQueue();

// Ritorna 1 se la coda e' vuota, altrimenti torna 0
int emptyQueue(Queue);

// Ritorna 1 se la coda e' piena, altrimenti torna 0
int fullQueue(Queue);

// Accoda un elemento nella struttura
// "err", passato per riferimetno dall'esterno
// restera' 0 se non ci sono errori
// altrimenti se l'accodamento non va a buon fine
// poiche' la coda e' piena, err sara' uguale a 5
void enqueue(Queue, int, int*);

// Toglie un elemento dalla struttura
// "err", passato per riferimetno dall'esterno
// restera' 0 se non ci sono errori
// altrimenti se il decodamento non va a buon fine
// poiche' la coda e' vuota, err sara' uguale a 6
int dequeue(Queue, int*);

// Stampa la coda
void printQueue(Queue, int*);

// Data una coda (gia' inizializzata) in ingresso
// e una dimensione (come secondo parametro)
// ed un terzo parametro per tenere traccia dell'errore
// popola la coda con valori random
void randQueue(Queue, int, int*);


//capovolge la coda data in input
void reverseQueue(Queue , int *);
#endif
