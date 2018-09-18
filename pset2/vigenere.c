#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[])
{
    //checa que solo des una palabra para el giro
    if (argc != 2) 
    {
        printf("Wroooong\n");
        return 1;
    }
    else
    {
        //convierte el input a string
        string k = argv[1];
        int o = strlen(k);
        printf("Ener plaintext:\n");
        string p = GetString();
        int n = strlen(p);
        int i; int z; int a = 0;
        //crea una matriz del largo de tu respuesta
        char res[n];
        printf("super pre r = %s \n",res);
        //checa letra por letra para hacer la transformacion
        for (i = 0; i < n; i++)
        {
            int j;
            printf("i=%i\n",i);
            ////////////creando el k correcto
            //rotamos k en caso de que el plaintext sea mayor a k
            if (i> (o-1))
            {
                int i0 = i/o;
                j = i - i0*o - a;
                // a es un contador de caracteres no letricos
            }
            else
                j = i - a;
                
          //convertimos la letra del k a número
            char z0 = k[j];
            int z1 = z0;
            printf("i= %i, j=%i, z0 = %i, z1 = %i\n",i,j,z0,z1);
            
            //k mayúcula o minúscula
        if ((z1 < 91) && (z1 > 64))
            z = z1 - 64;
        else if ((z1 < 123) && (z1 > 96))
            z = z1 - 96;
        else
          {
            printf("no es texto! j= %i, z1 = %i",j,z1);
            return 1;
          }
            
            
            //convertimos la letra del plaintext a número
            char y0 = p[i];
            int y = y0;
            int y1;
            
        
            //convierte mayúsculas
            if ((y < 91) && (y > 64))
            {
                y1 = y + z;
                    if (y1 > 90) 
                    y1 = y1-26;
                
            }
            //convierte minúsculas
            else if ((y < 123) && (y > 96))
            {
                y1 = y + z;
                    if (y1 > 122) 
                    y1 = y1-26;
            }
            else
            y1 = y;
            a = a+1;
           char y2 = y1;
           printf("pre res = %s \n",res);
           res[i]= y2;
          printf("i = %i,y1=%i,y2 =%c, r= %s\n",i,y1,y2,res);
        
        }
        printf("%s\n",res);
        
        return 0;
    }
}

// checar si y1 se pasa de 122 restar 96
// armar el resultado en una matriz con las y1s