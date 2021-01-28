//20/21 - 01 -21

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


int multiplicacion(int a, int b)
{
    return a * b;
}

int potencia(int base, int power)
{
    return pow(base, power);
}

int division(int a, int b)
{
    return a / b;
}

int validacion(char *a, char *b)
{
    int length = strlen(a);
    for(int i = 0; i < length; i++)
    {
        if(!isdigit(a[i]))
        {
            return 0;
        }
        
    }

    length = strlen(b);
    for(int i = 0; i < length; i++)
    {
        if(!isdigit(a[i]))
        {
            return 0;
        }
    }

    return 1;
}