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
#include <strings.h>
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
unsigned int check_word_count = 0;
unsigned int total_check_words = 0;

const unsigned int N = 4096; //adjust this

// Hash table
node *table[N]; //array of node-pointers
node *new_node = NULL;
node *head = NULL;
node *next = NULL;
// Returns true if word is in dictionary else false
bool check(const char *word)
{

 //todo

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) //working
{
    // HASH ALGORITHM
    // URL:     http://www.cse.yorku.ca/~oz/hash.html
    // Author: "first reported by Dan Bernstein"
    // Description: djb2
    //          This algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c.
    //      another version of this algorithm (now favored by bernstein) uses xor:
    //      hash(i) = hash(i - 1) * 33 ^ str[i];
    //      the magic of number 33 (why it works better than many other constants, prime or not)
    //      has never been adequately explained.
        unsigned long hash = 5381;
        int c;

        //c = each char of word, 1 by 1 (because ++)
        while ((c = *word++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c

        //too large for table?
        if (hash >= N)
            hash = hash % N;

        return hash;
}
    /*

    Idea borrowed from:
            http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
        As explained and demonstrated by the author,
        Prof. CS:YaleU,
            James Aspnes.

    Just seemed simple.

    const int BASE = N;
    const int MULTIPLIER = 31;
    unsigned int hash;
    unsigned const char *uc;
    for (uc = (unsigned const char *) word; *uc; uc++)
    {
        hash = (hash * MULTIPLIER + *word) % BASE;
    }
    return hash;

    */



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary) //working -- needs improvement
{
    //to add a word, create a new node
    //malloc space for new node
    //check new node not null
    //assign new node word
    //assign new node next (null)
    //assign table[key] to new node;

    //add another word, use same node
    //malloc same size of new node again
    //check new not not null again
    //assign new node word
    //assign new node next
    //assign table[key]->next to new node;

    //add another word again, use same node
    //malloc same size of new node again
    //check new not not null again
    //assign new node word
    //assign new node next
    //assign table[key]->next->next to new node;


    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL) return false;           //file failed

    new_node = malloc(sizeof(node));               //allocate memory for new node (declared globally)
    if (new_node == NULL) return false;            //no memory for allocation

    unsigned long file_size = 0;            //use for checking file-size
    unsigned int index = 0;
    char dword[LENGTH + 1];
    char nword[LENGTH + 1];

    while(fscanf(fp, "%s", dword) != EOF) //while(fscanf(fp, "%45s", n->word) != EOF)
    {
        dword_count++;
        index = hash(dword);

        strcpy(new_node->word, dword);
        new_node->next = NULL;

        table[index] = malloc(sizeof(node));
        if (table[index] == NULL)
            return false;

        strcpy(table[index]->word, new_node->word);

        table[index] = new_node;
        new_node->next = NULL;

        file_size = ftell(fp);                      //for debuggin
    }
    fclose(fp);
    printf("filesize: %lu\n", file_size);       //for debuggin
    printf("READING DICTIONARY COMPELTE\n");    //for debuggin



    return true;


}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dword_count;
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

