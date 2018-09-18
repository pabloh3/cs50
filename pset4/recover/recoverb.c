/**
 *recovers jpegs from a file
 */
       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int check(BYTE byt, FILE* inpt);
void printblock(FILE* inpt512, FILE* result512);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

 

    int counter = 0; int imagen = 0; BYTE byte;
    // iterate over file's bytes to find first image
   while (imagen ==0)
    {
        // read RGB triple from infile
        fread(&byte, sizeof(BYTE), 1, inptr);
        imagen = check(byte,inptr);
    }            
            // found first image
            
    counter = counter+1;
   char name[8];
    FILE *result;
   char* outfile = name;
    //if found new image, create new file, else continue adding blocks to previous image
    for (int i = 0; i < (8000000); i++)
    {
        if (imagen ==1)
            {
                //if not first file, close previous file
                 //   if (counter > 1)
                 //       {fclose(result);}
                        
                // open output file
               // if (counter <10)
                //{sprintf(name,"00%i.jpeg", counter);}
                //else
                {sprintf(name,"%i.jpeg", counter);}
                outfile = name;
                result = fopen(outfile, "w");
                if (result == NULL)
                    {
                        fclose(inptr);
                        fprintf(stderr, "Could not create %s.\n", outfile);
                        return 3;
                    }
                counter ++;
                printf("foto= %i i= %i",counter,i);
                imagen = 0;
                //break;
            }

        else
            {
                //printf("i %i imagen =%i\n",i,imagen);
                printblock(inptr,result);
                imagen = check(byte,inptr);
            }
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(result);

    // success
    return 0;
}




/* ya encontré dónde están las imágenes
hay que escibirlas en bloques de 512 bytes
1) cambiar el checador de foto a una funcion externa
2) checar que el siguiente bloque no sea una foto también, sino para incluirlo
5) cambiar el script para que lo repita una y otra vez, tal vez el chqueo 1) se vuelve una función externa
funcion sprintf para guardar los nombres de los archivos creados https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm

*/


int check(BYTE byt, FILE* inpt)
{
    
if (byt == 255)
    {
        fread(&byt, sizeof(BYTE), 1, inpt);
        if (byt == 216)
        {
            fread(&byt, sizeof(BYTE), 1, inpt);
            if (byt == 255)
            {
                fread(&byt, sizeof(BYTE), 1, inpt);
                if ((byt > 223) &&  (byt < 240))
                    {   
                        printf("una\n");
                        fseek(inpt, -4*sizeof(BYTE), SEEK_CUR);
                        printf("byte de una %u\n",byt);
                        return 1;
                    }    
                    else
                    {
                       fseek(inpt, -3*sizeof(BYTE), SEEK_CUR);
                        return 0;
                     }
        
            }
            else
            {
                fseek(inpt, -2*sizeof(BYTE), SEEK_CUR);
                return 0;
            }
        }
        else
        {
            fseek(inpt, -1*sizeof(BYTE), SEEK_CUR);
            return 0;      
        }
    }
return 0;
}


void printblock(FILE* inpt512, FILE* result512)
{
    BYTE byt512;
    for (int j = 0; j<5; j++)
        {   
            fread(&byt512, sizeof(BYTE), 1, inpt512);
             //printf("byte de printblock %u\n",byt512);
            fwrite(&byt512, sizeof(BYTE), 1, result512);
            //if (j<10)
           // {printf("byte = %u",byt512);}
        } 
}