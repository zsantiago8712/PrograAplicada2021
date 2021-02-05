#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void modificar_archivo(char *name, char *name2)
{
    printf("%s\n", name);
    FILE *fp, *fp1;
    char letra;
    
    fp = fopen(name, "r");
    fp1 = fopen(name2, "w");


    while(fscanf(fp, "%c", &letra) == 1)
    {
        letra = toupper(letra);
		fprintf(fp1, "%c", letra);

	}
    fclose(fp);
    fclose(fp1);




    


}