#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

Tree randomTree(int index) {
    int i = 0;
    Tree T = NULL;
    for (i = 0; i < index; i++) {
        T = insertNodeTree(T, rand() % 40);
    }
    return T;
}

Tree initNode(int info) {
    Tree T = (Tree)malloc(sizeof(struct TTree));
    T->info = info;
    T->sx = NULL;
    T->dx = NULL;
    return T;
}

Tree insertNodeTree(Tree T, int info) {
    if (T == NULL) {
        T = initNode(info);
    } else {
        if (T->info > info) {
            T->sx = insertNodeTree(T->sx, info);
        } else if (T->info < info) {
            T->dx = insertNodeTree(T->dx, info);
        }
    }
    return T;
}


void inOrder(Tree T) {
    if (T != NULL) {
        inOrder(T->sx);
        printf("%d ", T->info);
        inOrder(T->dx);
    }
}

void preOrder(Tree T) {
    if (T != NULL) {
        printf("%d ", T->info);
        preOrder(T->sx);
        preOrder(T->dx);
    }
}

void postOrder(Tree T) {
    if (T != NULL) {
        postOrder(T->sx);
        postOrder(T->dx);
        printf("%d ", T->info);
    }
}

void freeTree(Tree T)
{
	if(T)
	{
		freeTree(T->sx);
		freeTree(T->dx);
		free(T);
	}
}
