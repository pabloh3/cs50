#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //declaras tu nombre
    string n = GetString();
    //imprime la primera inicial
    int x = n[0];
    int x1;
    //checa si es minuscula para pasarla a mayuscula
    if (x > 95)
    x1 = x - 32;
    else 
    x1 = x;
    printf("%c",x1);
    //declara un espacio en blanco y lo busca con for en el string, si lo encuentra imprime la sig letra
    char blank = ' ';
        int i; int y;
        for (i = 0; i < (strlen(n)+1); i++)
        {
            //printf("%c\n",n[i]);
            if (n[i] == blank)
           {
            y = n[i+1];
            int y1;
            //convierte a mayuscula
                if (y > 95)
                y1 = y - 32;
                else 
                y1 = y;
            //printf("i=%i\n",i);
            printf("%c",y1);
            }
        }
printf("\n");
}


// capitalize restandole 32 al char que sea mayor a 95