#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int num = 1;
    char cadena[20] = "1234 Juan 19 500.34";
    char name[20] = { 0 };
    int n;
    float a;

    // num = atoi(cadena); // de alfanumerica  / string a int
    // a = atof(cadena); // de alfanumerica / string a float

    // scanf("%<tipo>", &<variable>);
    //scanf("%d", &num);



    // sscanf(<cadena>,"%<tipo>", &<variable>); 
    // Gurdan  cada palabra de u string en una varibale   
    sscanf(cadena, "%d %s %d %f", &num, name, &n, &a); // => los arreglos no necesitan &

    printf("%d %.2f\n", n, a);

    sprintf(cadena, "Hola a todos %d\n", num); //=> "Hola a todos 1234" => concatena strings con variables aunque sean de diferentes tipos de variables
    printf("%s", cadena);
    
}






