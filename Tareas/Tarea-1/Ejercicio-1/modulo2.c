#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int numero_de_lineas_archivo(char *file_to_read);




extern void read_and_write(char *file_to_read, char *file_to_write)
{

    int num_lineas = 0; 
    num_lineas = numero_de_lineas_archivo(file_to_read);

    FILE *fp, *fp1;
    fp = fopen(file_to_read, "r");
    fp1 = fopen(file_to_write, "w");
    char line[num_lineas];
    int a = 0;
    

    while(fgets(line, num_lineas, fp))
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
        a++;
    }  
    fclose(fp);
    fclose(fp1);



}

//Esta funcion cuneat los numeros de lianeas que hay en el archivo y los retorna
int numero_de_lineas_archivo(char *file_to_read)
{
    FILE *fp;
    fp = fopen(file_to_read, "r");
    char letra;
    int num_lineas = 0;

    while(fscanf(fp, "%c", &letra) != EOF)
    {
        if(letra == 10)
        {
            num_lineas++;
        }
    }
    return num_lineas;
}