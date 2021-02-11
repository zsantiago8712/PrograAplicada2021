#include <stdlib.h>
#include <stdio.h>



// La funcion (read_and_write) recibe el nombre de archvios que dio el usario, 
// el primero arhcivo es para leer linea por linea lo que tiene y cambiar las vocales que esten
// por '?' y el segundo es para escibir los cambios.
extern void read_and_write(char *file_to_read)
{

    FILE *fp, *fp1;
    fp = fopen(file_to_read, "r");
    char line[80];
    
    

    while (fread(line, sizeof(char), 1, fp) == 1)
    {
        printf("%s", line);
    }
    
    fclose(fp);



}

