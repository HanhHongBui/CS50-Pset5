/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */
//check50 2015.fall.pset5.speller dictionary.c dictionary.h Makefile 
//new
// check50 2016.speller dictionary.c dictionary.h Makefile
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"


node* root;
int word_count = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int len = strlen(word);
    int index;
    node* current = root;
    
    for(int i = 0; i < len; i++)
    {   // if the character is alphabetic, convert it to lower case
        if(isalpha(word[i]))
            tolower(word[i]);
        int c = word[i];    
        index = GetIndex(c);
        
        if(current->children[index]==NULL)
        {
            return false;
        }
        current = current->children[index];
    }
    if (current->is_word == true)
    {
        return true;
    }
    else
    return false;
}
/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)

{  
    //open dictionary
    FILE* fp = fopen(dictionary,"r");
    if (fp==NULL)
    {
        return false;
    }
    //iterate over each char in the dictionary, make a new children array
      root = malloc(sizeof(node));
    node* cursor = root;
    
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {   //end of line
        if (c == '\n')
        {
            cursor->is_word = true;
            cursor = root;
            word_count++;
        }
        else
        //if char is alphabetic or ' 
        {
            int index = GetIndex(c);
            if(cursor->children[index]==NULL)
            // create a new node
            {
                cursor->children[index] = malloc(sizeof(node));
            }
            //continue to the next node
            cursor = cursor->children[index];
        }
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
   
        return word_count;
    
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
void clear(node* ptr)
{
    for (int i = 0; i <27; i++)
    {
        if(ptr->children[i] != NULL)
        clear(ptr->children[i]);
    }
    free(ptr);
}
bool unload(void)
{
    clear(root);
    return true;
}
void clear(node* ptr);

int GetIndex (int c)
    { // ' case 
       if (c==39)
        return 26;
        //lower case
    
    else if (c>=97 && c<=122)
        return (c-97);
        //upper case
    
    else if (c >=65 && c <=90)
        return (c-65);
    
    else
    return -1;
    }
