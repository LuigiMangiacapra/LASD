#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tree.h"

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    
    // Creo un nuovo albero T da 10 nodi
    Tree T = randomTree(10);
    
    // Eseguo una In Order sull'albero T
    inOrder(T);
    
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

