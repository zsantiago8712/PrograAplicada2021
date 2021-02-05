#include <stdlib.h>
#include <stdio.h>


extern void copiar_archivos(char *name, char *name2);

int main(int argc, char *argv[])
{
    
   if(argc < 2)
   {
       printf("Error se necesita mas argumentos\n");
       exit(0);
   }

    char *nombre = "text.txt";
    copiar_archivos(nombre, argv[1]);

}