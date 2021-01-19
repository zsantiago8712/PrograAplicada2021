// Programa que conecta archivos .c

#include <stdio.h>
#include <stdlib.h>


typedef struct datos{
    int x;
    int y;

}DATOS;


extern int suma(int x, int y);  // extern --> le dice al la pc que la funcion no esta en este archivo
extern int resta(int x, int y);


int main(void)
{
    int a, b, c, d;
    b = 1;
    c = 2;
    a = suma(b, c);
    d = resta(c, b);
    printf("%d %d\n", a, d);
}

//Para compilar gcc -o Archivo-final.out  archivo-1.c archivo-2.c archivo-3.c y los que quieran qu se compile