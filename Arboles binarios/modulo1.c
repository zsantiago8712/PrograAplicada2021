#include "local.h"

extern void insertar(ARBOL **inserccion, int num);
extern void imprimir(ARBOL *raiz);
extern void liberar_memoria(ARBOL *raiz);
extern long fibo(int num);

int main(void)
{
    int num;
    int cero = 0;
    ARBOL *raiz;
    raiz = NULL;

    printf("Introduce in numero y ctrl-d para salir:\n");
    scanf("%d", &num);
    // while(num != cero)
    // {
    //     printf("%ld - ", fibo(cero));
    //     cero++;
    // }
    while(scanf("%d", &num) == 1)
    {
        insertar(&raiz, num);
    }
    system("clear");
    imprimir(raiz);
    liberar_memoria(raiz);
}

