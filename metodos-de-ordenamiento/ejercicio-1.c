#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


void quicksort(char *nombres[], int fin);

int main(void)
{
    FILE *fp;
    int i = 0;
    char *nombres[16];
    char nombre[200];
    fp = fopen("listaA", "r");
    while(fgets(nombre, 200, fp) != 0)
    {
        nombres[i] = strdup(nombre);
        i++;
    }

    quicksort(nombres, 15);

    for(int i = 0; i < 15; i++)
    {
        printf("%s\n", nombres[i]);
    }



}

void quicksort(char *nombres[], int fin)
{
    int i = 0; int j = fin - 1;

    char *pivote = nombres[j / 2], *temp;

    do
    {
        while(strcasecmp(strdup(nombres[i]), pivote)  < 0)
        {
            i++;
        }

        while(strcasecmp(strdup(nombres[j]), pivote)  > 0)
        {
            j--; 
        }

        if(i < j)
        {
            temp = strdup(nombres[i]);
            nombres[i] = strdup(nombres[j]);
            nombres[j] = strdup(temp);
            
        }else if(i > j)
        {
            break;
        }
    }while(++i <= --j); 

    if(j > 0)
    {
        quicksort(nombres, j + 1);
    }

    if(i < fin - 1)
    {
        quicksort(nombres + 1, fin - 1);
    }



    



}