#include <stdio.h>
#include <stdlib.h> 
#include <malloc.h> main() 
int main(){
int numero=100, allocati, *array, i; char buffer[15];
printf("Numero di elementi dell'array: %d", numero);
array = (int *)malloc(sizeof(int) * numero);
if(array == NULL) { printf("Memoria esaurita\n"); exit(1); }
allocati = sizeof(int) * numero;
for(i=0; i<numero; i++) array[i] = i;
printf("\nValori degli elementi \n");
for(i=0; i< numero; i++) {
	printf("%d", array[i]);
	if(i != numero-1){
		printf("->");
	}
}
printf("\n\nNumero elementi %d \n", numero);
printf("Dimensione elemento %d \n", sizeof(int));
printf("Bytes allocati %d \n", allocati);
free(array); 
printf("\nMemoria Liberata \n"); 
} 

