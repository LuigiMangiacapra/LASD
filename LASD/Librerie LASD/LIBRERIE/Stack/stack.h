#ifndef Library_stack_h
#define Library_stack_h
#define STACK_MAX 128

struct TStack{
	int A[STACK_MAX+1];
};

typedef struct TStack* Stack;

Stack initStack();
int emptyStack(Stack);
int fullStack(Stack);
void push(Stack, int, int*);
int pop(Stack, int*);
void reverseStack(Stack, Stack, int*);
void printStack(Stack, int*);
void randomStack(Stack S, int n, int *err);

#endif
