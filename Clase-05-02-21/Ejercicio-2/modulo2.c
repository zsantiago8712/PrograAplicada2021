#include <stdio.h>
#include <stdlib.h>

void copiar_archivos(char *name, char *name2)
{
    printf("%s\n", name);
    FILE *fp, *fp1;
    char letra;
    
    fp = fopen(name, "r");
    fp1 = fopen(name2, "w");


    while(fscanf(fp, "%c", &letra) == 1)
    {
		fprintf(fp1, "%c", letra);
	}
    fclose(fp);
    fclose(fp1);


    


}