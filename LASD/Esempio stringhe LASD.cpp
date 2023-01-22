#include <stdio.h>
main()
{
	char *giorni[7] = { "Lunedi" , "Martedi" , "Mercoledi" , "Giovedi" , "Venerdi" , "Sabato" , "Domenica" };
	int i;
	for( i = 0; i < 7; i++) 
	{
		if(i==5){
			printf( "\nstringa: %s, con indirizzo: %d ", giorni[i], *giorni[i]);
			char *str = giorni[i]; //cattura della stringa
			int j=0;
			
			//cicla la stringa
			while(str[j] != '\0'){
				if(j==2){
					printf("%c" , str[j]);
				}
					j++;
			}
		}
	}
}

