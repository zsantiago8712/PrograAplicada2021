#include <stdlib.h>
#include <stdio.h>



/* La funcion (read_and_write) recibe el nombre de archvio que dio el usario, 
    lee paquete por paquete con un tamaño de un byte para imprimirlo en la terminal
*/ 
void read_and_print(char *file_to_read)
{
    
    char line[10];
    FILE *fp;
    
    fp = fopen(file_to_read, "r");
    if(fp == NULL)
    {
        printf("ERROR: El archvivo no existe\n");
        exit(0);
    }
    
    
    while (fread(line, sizeof(char), 1, fp) == 1) //Se asume que los paquetes tienen un tamaño de 1 byte
    {
        printf("%s", line);
    }
    printf("\n");
    fclose(fp);

}

