#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
    const char *dictionary = "speller/dictionaries/large";
    FILE *pt = fopen(dictionary, "r");

    unsigned long long int word_count = 0;
    unsigned long int char_count = 0;
    unsigned long int null_count = 0;
    unsigned int apostrophe_count = 0;

    char *word = NULL;
    char *c, a;
    int size = (sizeof(char *) * char_count);
    c = malloc(sizeof(size));

    /*
        NOT WORKING
    */

    while(fgetc(pt))
    {
        char_count++;
        a = fgetc(pt);
            if (a == '\0') null_count++;
            if (a == '\n') {
                word = malloc(size);
                word[char_count] = a;
                word_count++;
            }
            if ((int)a == 39) apostrophe_count++;
    }
    printf("Counts:\n\tCHARS: %lu\n\tWORDS: %llu\n\t APOSTROPHEs: %u\n", char_count, word_count, apostrophe_count);
    fclose(dictionary);
}