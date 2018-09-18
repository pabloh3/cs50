/**
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>
sllnode* start = {NULL};


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    
    //load the dictionary file for reading
FILE *inptr = fopen(dictionary, "r");

//read dictionary
    //initialize reelvant variables
char x = 'a'; int count = 0; char word1[47];
//crear una función que se llame a si misma para leer las palabras y guardarlas???
//read till you finish with a word

while (!feof(inptr))
{
    while(x != '\n')
    {
        fread(&x,sizeof(x), 1, inptr);
        
        word1[count] = x;
        count++;
        printf("letra start = %i\n",count); 
    }
    
    printf("palabra start = %s\n",word1);
    //create start node
        
    // define start node of the dictionary
    //allocate memory
    start = malloc(sizeof(sllnode));
    //check that it doesn't point to null
    if (start == NULL)
    {
        free(start);
        return false;
    }
        strcpy( start->word, word1);
        start->next = NULL;
}


int not_eof = 1; int wcount = 0;
//mientras no se llegue a end of file, extrae palabras
while (not_eof==1)
    {
        //mientras no se llegue a end of word, extrae letras
        while(x != '\n')
        {
            fread(&x,sizeof(x), 1, inptr);
            printf("char = %c\n",x);
            word1[count] = x;
            count++;
            
            //checa si se llego a end of file
            if (feof(inptr))
            {
             not_eof = 0;
             x=0;
             return true;
            }
           
        }
        
        wcount ++;
        printf("palabra = %s\n",word1);
    
    //guarda las palabras en un nuevo nodo
    sllnode* node = malloc(sizeof(sllnode));
    strcpy( node->word, word1);
    node->next = start;
    start = node;
    
        x=0;
    }

/*sllnode* verif = start.next;
printf("palabra2 = %s",verif.word1);*/


//close reading file
fclose(inptr);
    
return false;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
 /*  sllnode* cursor = {NULL};
   cursor = start;
   while (cursor != NULL)
   {
       cursor = cursor -> next;
       if (strcasecmp(word,cursor->word) == 0)
       return true;
       
   }*/
    return false;
}



/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
sllnode* tmp;
char word2[47];
if (start == NULL)
return false;
   while (start != NULL)
    {
       tmp = start;
        strcpy(word2, tmp->word);
       printf("node %s\n",word2);
       start = tmp->next;
       free(tmp);
    }
    return true; 
}
