#include <stdio.h>
#include <stdlib.h>

#define MAX 50



int main(void)
{
    FILE *fp;
    int data, count, arreglo[MAX];
    long offset;


    for(count = 0; count < MAX; count++)
    {
        arreglo[count] = count * 10;
    }

    fp = fopen("datos.dat", "wb");
    fwrite(arreglo, sizeof(int), MAX, fp);
    fclose(fp);

    fp = fopen("datos.dat", "rb");
    if(fp == NULL)
    {
        printf("ERROR: No existe el archivo");
        exit(0);
    }

    while(1)
    {
        printf("Tecelee el indice del elemento a leer de o a %d, y -1 para salir: ", MAX - 1),
        scanf("%ld", &offset);

        if(offset < 0)
        {
            break;
        }
        else if(offset > MAX - 1)
        {
            continue;
        }
        fseek(fp, offset * sizeof(int), SEEK_SET);
        fread(&data, sizeof(int), 1, fp);
        printf("El valot en la posicion %ld es %d\n", offset, data);

    }

    fclose(fp);

}
