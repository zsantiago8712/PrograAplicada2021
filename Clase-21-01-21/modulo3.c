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

int validacion(char a[20], char b[20])
{
    int length = strlen(a);
    for(int i = 0; i < length; i++)
    {
        if(!isdigit(a[i]))
        {
            return 1;
        }
        
    }

    length = strlen(b);
    for(int i = 0; i < length; i++)
    {
        if(!isdigit(a[i]))
        {
            return 1;
        }
    }

    return 0;
}