/*29 - 01 - 21

                    Ejemplos de manejo de archivos

*/

#include <stdio.h>
#include <stdlib.h>



extern int sumaNumeros(char *nombre);  
extern void guardarNumeros(char *nombre, int numeros[]);


int main(void)
{
    int numeros[10];
    int resultado;
    char *nombre_archivo = "numeros.txt";

    printf("Dame 10 números:\n");
    for(int i = 0; i < 10; i++)
    {
        printf("%d.- ", i + 1);
        scanf("%d", &numeros[i]);
    }
    guardarNumeros(nombre_archivo, numeros);
    resultado = sumaNumeros(nombre_archivo);
    printf("La suma de los números es: %d\n", resultado);   



}