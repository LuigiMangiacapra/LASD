#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, const char * argv[]) {
    
    // Inizializzo una variabile nel main di errore
    int err = 0;
    
    // Inizializzo una coda
    Queue coda = initQueue();
    
    // Creo una coda random di 10 elementi
    randQueue(coda, 10, &err);
    
    // Stampo la coda
    printQueue(coda, &err);
    return 0;
}
