#include "local.h"

void extern opcion(int argc, char *argv[]);


int main(int argc, char *argv[])
{
    if(argc < 2 || argc > 5)
    {
        printf("ERROR: de argumentos, para ayuda introduzca -h\n");
        exit(1);
    }else
    {
        opcion(argc, argv);
    }
}