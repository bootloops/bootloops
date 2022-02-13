// Implements a dictionary's functionality
//
//EDIT THIS FILE TO MAKE SPELL CHECK WORK!
//
// Load
/*
    Step ONE:
     Load dictionary
     Read strings from file one at a time
     Create a new node for each word
     Hash word to obtain a hash value
     Insert node into hash table at that value location
     Hash value cannot be greater or smaller than the hash table

    Open dictionary and store all words into hash table
    simple dictionary: apple banana bat car book
    BUCKETS:
        a -> apple

        b -> bat -> book -> banana

        c -> car

    Hash function takes the word, hashes a value and that is the index

*/

// Hash
/*
    take word as input
    output a number, corresponding to index where to store the word
    output can not be larger than the hash table
*/

// Size
/*  */
// Check
/*  */
// Unload
/*  */
//
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
unsigned int char_count = 0; //char count for transfering words
unsigned int dword_count = 0; //dictionary word count
unsigned int total_dwords = 0; //total word count to dump dword_count into
unsigned int check_word_count = 0;
unsigned int total_check_words = 0;
const unsigned int N = 1024; //adjust this

// Hash table
node *table[N]; //array of node-pointers
node *n = NULL;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //if word in dictionary, return true
    //perform same hash(check_word) which will return the same hash, and
    //then lookup that hash index to compare the word
    //if the word exists, return true
    //if not, return false
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) //working -- needs collisions checks
{
    /*
    Idea borrowed from:
            http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
        As explained and demonstrated by the author,
        Prof. CS:YaleU,
            James Aspnes.

    Just seemed simple.
    */
    #define BASE (N)
    #define MULTIPLIER (97)
    unsigned int hash;
    unsigned const char *uc;
    for (uc = (unsigned const char *) word; *uc; uc++)
    {
        hash = (hash * MULTIPLIER + *word) % BASE;
    }
    return hash;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary) //working -- needs improvement
{
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL) return false; //file failed

    char c[LENGTH + 1];
    //store the strings, no larger than 46[must be 46 > breaks.]
    char d_word[LENGTH + 1];
    for (int pop = 0; pop < N; pop++) table[pop] = NULL;

    while(fscanf(fp, "%45s", d_word) != EOF) //
    {
        total_dwords++;
        //FIND THE MAX NUMBER OF CHARS, FOR WORDS IN DICTIONARY/LARGE
        // while (*d_word != '\0')                      //scan chars until '\0'
        // {
        //     c[dword_count] = d_word[dword_count];   //read each char, c[dword_count] into
        //     char_count++;

        //     if (char_count > LENGTH) break; //too large to be one word
        // }

        n = malloc(sizeof(node));               //allocate memory for new node (declared globally)
        if (n == NULL) return false;            //no memory for allocation

        while(!EOF) strcpy(n->word, d_word); dword_count++;
        //ESSENTIALLY ABOVE REPLACES BELOW
        // while(dword_count < LENGTH)         //scan the dword into n->word[dword_count]
        // {
        //     n->word[dword_count] = d_word[dword_count];     //add the dword to the n node, char by char, using index positon [dword_count]
        //     dword_count++;                                  //count the words added
        // }

        unsigned int key = hash(d_word);
        if (table[key] == NULL)
        {
            n->next = table[key];   //point n->next to table[key] (new table)
            table[key] = n;         //point the table[key] to new node]
        }
        // for (int x = 0; x < LENGTH + 1; x++) //loop the dword, clear previous word
        //     d_word[x] = '\0';                //replace all chars in dword with null chars

        //free(n); //possibly freeing too soon?

    }
    return true;
    fclose(fp);

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int words_in_dict;
    words_in_dict = total_dwords;
    // TODO
    // printf("size() report: \n");
    // printf("counter: %i\n", counter);
    // printf("dword_count: %i\n", dword_count);
    // printf("char_count: %i\n", char_count);
    // printf("total_dwords: %i\n", total_dwords);
    // printf("check_word_count: %i\n", check_word_count);
    // printf("total_check_words: %i\n", total_check_words);
    return words_in_dict;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //if (n != NULL) free(n);
    //unload process

    return true;
}

                //how to populate hash table
                //allocate memory into a new node
                //node *n = malloc(sizeof(node)); //stores the address of the node
                //strcpy(n->word, "Hello");
                //n->next = NULL;

                //TODO
                //open dictionary file
                //--fopen(dictionary) //check for null if failed
                //--fscanf(file, "%s", word);
                //**fscanf will return EOF once it reaches end of file**
                //use a loop for fscanf
                //create a new node, malloc for node
                //remember to check if return null
                //strcpy(n->word, "string")

                //read strings from file one at a time
                //create a new node for each word
                //hash word to obtain hash value
                //insert node into hash table at that location (given by hash function)
                //strcasecmp() -- compares without case sensitivity


/*

        while(dword_count < LENGTH + 1)         //scan the dword into n->word[dword_count]
        {
            n->word[dword_count] = d_word[dword_count];     //add the dword to the n node at index positon [dword_count]
            dword_count++;                                  //count the words added
        }




*/