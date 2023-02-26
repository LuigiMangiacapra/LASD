# include <stdio.h>
# define MAX 20
int i,j; /* Indici di scorrimento dell'array */
void insertion(int interi[MAX],int tot);

main()
{
	int interi[MAX]; /* Array che contiene i valori da ordinare */
	int tot; /* Numero totale di elementi nell'array */
	printf("\n Quanti elementi deve contenere l'array: ");
	scanf("%d",&tot);
	while (tot>20) {
		printf("\n max 20 elementi: "); 
		scanf("%d",&tot); 
	}
	for (i=0;i<tot;i++){ 
		printf("\nInserire il %d° elemento: ",i+1); 
		scanf("%d",&interi[i]); 
	}
	insertion(interi,tot);
	printf("\nArray Ordinato:");
	for (i=0; i<tot; i++)
		printf(" %d",interi[i]);
}

void insertion(int interi[20],int tot)
{
	int temp; /* Indice temporaneo per scambiare elementi */
	int prossimo;
	int attuale;
	for (prossimo=1; prossimo<tot; prossimo++)//cicla sulla parte reputata "non ordinata" dell'array
	{
		temp=interi[prossimo];//primo elemento parte non ordinata
		attuale=prossimo-1;//elemento che precede il primo della parte non ordinata
		while ((attuale>=0) && (interi[attuale]>temp))//gestisce gli elementi da confrontare con la parte non ordinata
		{
			interi[attuale+1]=interi[attuale];
			attuale=attuale-1;
		}
		interi[attuale+1]=temp;
	}
}
