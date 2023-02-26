#include <stdio.h>
main()
{
int tabelline[10][10]; int i, j;
for (i = 0 ; i < 10 ; i++){

for(j = 0 ; j < 10 ; j++){

tabelline[i][j] = (i + 1) * (j + 1);
printf("%d ", tabelline[i][j]);
if(j==9)
	printf("\n\n");
}
}
}
