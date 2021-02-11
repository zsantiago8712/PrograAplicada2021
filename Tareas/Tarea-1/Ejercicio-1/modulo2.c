#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int numero_de_lineas_archivo(char *file_to_read);



// La funcion (read_and_write) recibe los dos nombres de archvios que dio el usario, 
// el primero arhcivo es para leer linea por linea lo que tiene y cambiar las vocales que esten
// por '?' y el segundo es para escibir los cambios.
extern void read_and_write(char *file_to_read, char *file_to_write)
{

    int num_lineas = 0; 
    num_lineas = numero_de_lineas_archivo(file_to_read);
    printf("%d\n", num_lineas);
    FILE *fp, *fp1;
    fp = fopen(file_to_read, "r");
    fp1 = fopen(file_to_write, "w");
    char line[80];
    int a = 0;
    

    while(fgets(line, 80, fp) == 1)
    {

        for(int i = 0; i < strlen(line); i++)
        {
            if(line[i] == 'a' || line[i] == 'e' || line[i] == 'i' || line[i] == 'o' || line[i] == 'u')
            {
                line[i] = '?';
            }else if(line[i] == 'A' || line[i] == 'E' || line[i] == 'O' || line[i] == 'U' || line[i] == 'I')
            {
                line[i] = '?';
            }
        }
        fputs(line, fp1);              
    }  
    fclose(fp);
    fclose(fp1);



}

