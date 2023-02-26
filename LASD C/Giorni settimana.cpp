#include <stdio.h>
main()
{
	//Array di indirizzi delle stringhe specificate
	char *giorni[7] = { "Lunedi" , "Martedi" , "Mercoledi" , "Giovedi" , "Venerdi" , "Sabato" , "Domenica" };
	//Automaticamente giorni[7] possiederà tutte le stringhe
	int i;
	for( i=0; i< 7; i++) 
	{
		printf( "\n %d " ,*giorni[i]);//Stampa il contenuto dell'array di puntatori, cioè gli indirizzi delle stringhe
		printf( "%s" ,giorni[i]); //Stampa le stringhe
	}
}
