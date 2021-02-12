#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int is_vocal(char letra);


// La funcion (read_and_write) recibe los dos nombres de archvios que dio el usario, 
// el primero arhcivo es para leer linea por linea lo que tiene y cambiar las vocales que esten
// por '?' y el segundo es para escibir los cambios.
extern void read_and_write(char *file_to_read, char *file_to_write)
{

    FILE *fp, *fp1;
    fp = fopen(file_to_read, "r");
    if(fp == NULL)
    {
        printf("ERROR: El archvivo no existe\n");
        exit(1);
    }
    fp1 = fopen(file_to_write, "w");
    char line[80];
    

    while(fgets(line, 80, fp) != 0)         //Se asume que la linea/renglon tiene un tamaño de 80 caracters
    {

        for(int i = 0; i < strlen(line); i++)
        {
            if(is_vocal(line[i]) == 1)
            {
                line[i] = '?';
            }

        }
        fputs(line, fp1);              
    }  
    fclose(fp);
    fclose(fp1);

    
}


int is_vocal(char letra) // Funcion para validar si es vocal
{
    letra = tolower(letra);
    if(letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u')
    {
        return 1;
    }
    return 0;
}

