/**
 *recovers jpegs from a file
 */
       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

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
    char *outfile = "result.jpeg";

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *result = fopen(outfile, "w");
    if (result == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

int counter = 0;
    // iterate over file's bytes
    for (int i = 0; i < (30000000); i++)
    {
            // temporary storage
            BYTE byte;

            // read RGB triple from infile
            fread(&byte, sizeof(BYTE), 1, inptr);
            //int leido = byte
            if (byte == 255)
            {
                fread(&byte, sizeof(BYTE), 1, inptr);
                if (byte == 216)
                {
                    fread(&byte, sizeof(BYTE), 1, inptr);
                    if (byte == 255)
                    {
                        fread(&byte, sizeof(BYTE), 1, inptr);
                        if ((byte > 223) &&  (byte < 240))
                        {
                            counter = counter+1;
                            fseek(inptr, -4*sizeof(BYTE), SEEK_CUR);
                            for (int j = 0; j<512; j++)
                            {   
                                fread(&byte, sizeof(BYTE), 1, inptr);
                                fwrite(&byte, sizeof(BYTE), 1, result);
                            }
                            printf("foto= %i i= %i",counter,i);
                            break;
                        }
                    }    
                }
                
            }
            // write RGB triple to outfile
            //fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
       
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