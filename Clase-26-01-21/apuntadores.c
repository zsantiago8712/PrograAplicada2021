#include <stdio.h>
#include <stdlib.h>

int suma(int *x, int *y);

int main(void)
{
    int x = 5;
    int y = 4;

    suma(&x, &y);
    printf("%d %d\n", x, y);

}

int suma(int *x, int *y)
{
    (*x)++;     /* ----> para poder modificar el valor debes poner (*variable) significa que trae el valor 
                y despues lo modifica en el caso le suma 1*/
    (*y)++;
    
    
    

}