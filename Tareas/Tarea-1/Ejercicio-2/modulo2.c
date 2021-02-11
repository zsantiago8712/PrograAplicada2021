#include <stdlib.h>
#include <stdio.h>



/* La funcion (read_and_write) recibe el nombre de archvio que dio el usario, 
    lee paquete por paquete con un tamaño de un byte para imprimirlo en la terminal
*/ 
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

