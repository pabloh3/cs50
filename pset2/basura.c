#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
   int k= 112;
   int y = k/50;
   int z = k-y*50;
   printf("k = %i, y = %i, z = %i",k,y,z);
}