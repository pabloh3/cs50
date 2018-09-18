/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 
bool search(int value, int values[], int n)
{
   /*                   int a;
   for (a=0; a<n; a++)
   {
   printf("a =%i, values_res=%i \n", a, values[a]);
   } */
     for (int i = 0; i < n; i++)
        {

            
            if (values[i] == value)
                return true;
        }
        return false;
}


 
 //funcion que compara 2 numeros y regresa 1 si el primero es mayor, regresa 0 si el segundo
int compare(int valueA, int valueB)
    {
     if (valueA > valueB)
     return 1;
     return 0;
    }

 /**
 * Sorts array of n values.
 */
 //bubble sort
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int cambios; int res; int res2;
   for (int j = 0; j < 65536; j++) 
   {
    cambios = 0;
    int v1; int v2;
       for (int i = 0; i < (n-1); i++)
        {
            v1 = values[i]; v2 = values[i+1];
           res = compare(v1,v2);
            cambios = cambios + res;
            if (res == 1)
            res2 = 0;
            else
            res2 = 1;
            values[i] = v1*res2 + v2*res;
            values[i+1] = v1*res + v2*res2;
              
               
        }
        if (cambios == 0)
        break;

   }
  
    return;
}
