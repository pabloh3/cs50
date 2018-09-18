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
    char x = 'a'; int count = 0; char* word1 = malloc(48);
    //crear una función que se llame a si misma para leer las palabras y guardarlas???
    //read till you finish with a word
    
    
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
    
    free(word1);
   word1 = malloc(48);
    
    
    int not_eof = 1; int wcount = 0; count = 0; x=0;
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
                 break;
                }
               
            }
            
            if (not_eof != 0)
            {
                wcount ++;
                printf("palabra = %s\n",word1);
                count = 0;
                
                //guarda las palabras en un nuevo nodo
                sllnode* node = malloc(sizeof(sllnode));
                
                strcpy( node->word, word1);
                //printf("new node createdd = %s\n",word1);
                node->next = start;
                start = node;
                
                free(word1);
                word1 = malloc(48);
                x=0;
            }
        }
        fclose(inptr);
        free(word1);
        return true;
    
    /*sllnode* verif = start.next;
    printf("palabra2 = %s",verif.word1);*/

}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
  sllnode* cursor = {NULL};
   cursor = start;
   int len = strlen(word);
   char temp[len+1];
   for(int i = 0; i<len; i++)
   {
       temp[i] = word[i];
   }
 
   temp[len]= '\n';
   temp[len+1]= '\0';
   
   while (cursor != NULL)
   {
       printf("-word = %s\n-",temp);
       printf(".dictionary_word = %s\n.",cursor->word);
       if (strcasecmp(temp,cursor->word) == 0)
       return true;
       cursor = cursor -> next;
       
   }
    return false;
}



/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    sllnode* cursor = {NULL};
   cursor = start;
   int count = 0;
   while (cursor != NULL)
   {
       count++;
       cursor = cursor -> next;
       
   }
    return count;
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
