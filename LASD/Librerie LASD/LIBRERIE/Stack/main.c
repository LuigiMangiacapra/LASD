#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Stack S=initStack(),T=initStack();
	int e=0;
	randomStack(S,20,&e);
	randomStack(T,20,&e);
	printStack(S,&e);
	printf("\n\n");
	printStack(T,&e);
	free(T);
	free(S);
	return 0;
}
