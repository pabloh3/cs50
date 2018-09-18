/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    int rs = atoi(argv[1]);
    // ensure proper usage
    if ((argc != 4)||(rs>100)|| (rs<0))
    {
        fprintf(stderr, "Usage: ./resize resize_float infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
 /*   { 
    WORD bfType; 
    DWORD bfSize; 
    WORD bfReserved1; 
    WORD bfReserved2; 
    DWORD bfOffBits; 
} __attribute__((__packed__)) 
BITMAPFILEHEADER; */

//printf("bfsize = %u",bf.bfSize);



    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
 /*   {
    DWORD biSize; 
    LONG biWidth; 
    LONG biHeight; 
    WORD biPlanes; 
    WORD biBitCount; 
    DWORD biCompression; 
    DWORD biSizeImage; 
    LONG biXPelsPerMeter; 
    LONG biYPelsPerMeter; 
    DWORD biClrUsed; 
    DWORD biClrImportant; 
} __attribute__((__packed__))
BITMAPINFOHEADER; */

       
 // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

// determine padding for scanlines
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

//adjust new width and heitgh
bi.biWidth = bi.biWidth*rs;
bi.biHeight = bi.biHeight*rs;

// determine padding for outlines
int padding2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

bi.biSizeImage = ((sizeof(RGBTRIPLE)*bi.biWidth)+padding2)*abs(bi.biHeight);
bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

   

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    
 
   
    
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight/rs); i < biHeight; i++)
        {
           for (int l = 0 ; l < rs; l++)
             {
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth/rs; j++)
                {
                     // temporary storage
                        RGBTRIPLE triple;
                        // read RGB triple from infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                   for(int m = 0; m<rs; m++)
                    {
                       
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                        /*printf("i=%i j=%i l= %i m=%i\n",i,j,l,m);
                            //BYTE rgbtBlue;
                            //BYTE rgbtGreen;
                            //BYTE rgbtRed;
                        printf("RGB=%u%u%u\n",triple.rgbtBlue,triple.rgbtGreen,triple.rgbtRed);*/
                    }
                    
                }
                //add padding
                     for (int k = 0; k < padding2; k++)
                    {
                        fputc(0x00, outptr);
                    }
        
                // skip over padding, if any
                fseek(inptr, padding, SEEK_CUR);
                if (l!=(rs-1))
                {//volver a leer linea anterior
                long row_length = (padding+sizeof(RGBTRIPLE)*bi.biWidth/rs);
                fseek(inptr, -1*row_length, SEEK_CUR);
                }
                
             }
        }
    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

