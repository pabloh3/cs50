/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
 
 //define una funcion que luego usará
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // solo te deja meter 2 o 3 argumentos a la funcion, si no lo haces te indica  "Usage: generate n [s]"
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // convierte tu input de cuantos tumeros quieres a numero
    int n = atoi(argv[1]);

    // si usas un seed te convierte tu seed a numero y lo usa como argumento para srand48
    // si no pones seed usa el tiempo actual como seed (time(null) te da los segundos desde enero del 71)
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }
    // corre la funcion dranrd48 para generar aleatorios
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}