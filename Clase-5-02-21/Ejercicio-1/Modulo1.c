#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


extern void modificar_archivo(char *name, char *name2);


int main(int argc, char *argv[])
{
    
   if(argc < 2)
   {
       printf("Error se necesita mas argumentos\n");
       exit(0);
   }

    char *nombre = "text.txt";
    modificar_archivo(nombre, argv[1]);

}


