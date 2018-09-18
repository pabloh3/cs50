#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[])
{
    //checa que solo des un numero para el giro
    if (argc != 2) 
    {
        printf("Wroooong\n");
        return 1;
    }
    else
    {
        //printf("Ener plaintext:\n");
        string p = get_string();
        //printf("Argc = %i, plaintext =%s\n",argc,p);
        //convierte el input a numero
        int k = atoi(argv[1]);
        int l = k/26;
        int m = k-l*26;
        int n = strlen(p);
        int i;
        //crea una matriz del largo de tu respuesta
        char r[n];
        printf("pre r = %s",r);
        //checa letra por letra para hacer la transformacion
        for (i = 0; i < (n); i++)
        {
            char y0 = p[i];
            int y = y0;
            int y1;
            
            //convierte mayúsculas
            if ((y < 91) && (y > 64))
            {
                y1 = y + m;
                    if (y1 > 90) 
                    y1 = y1-26;
                
            }
            //convierte minúsculas
            else if ((y < 123) && (y > 96))
            {
                y1 = y + m;
                    if (y1 > 122) 
                    y1 = y1-26;
            }
            else
            y1 = y;
           char y2 = y1;
           r[i]= y2;
          // printf("i = %i, k= %i,y1=%i,y2 =%c\n",i,k,y1,y2);
        }
        printf("%s\n",r);
        
        return 0;
    }
}

// checar si y1 se pasa de 122 restar 96
// armar el resultado en una matriz con las y1s