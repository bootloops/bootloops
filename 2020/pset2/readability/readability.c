#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

//FUNCTIONS
int letter_count(string txt);
int word_count(string txt);
int sentence_count(string txt);
void check_input(string txt);
void output_numbers(void);
void grade_calc(string txt);
void get_user_input(void);

//STRINGS
string text; //global input text string

//INT
int x, sentence, l, letters, space, words;
//[x]global counter, [L]avg letter count, [S]avg sentence count, [P]special chars, [N]number chars, [C]capital chars, [l]letters count [SPACE]word count, [W]words

//DOUBLES
double S, L, index;

//CHARS
char ends[3] = {'.', '?', '!'};

//MAIN
int main(void)
{
    get_user_input();       //user input text
    letter_count(text);     //count letters
    word_count(text);       //count words
    sentence_count(text);  //count sentences
    //output_numbers();     //debugging output
    grade_calc(text);       //calculate grade level with CLI
}

//FUNCTIONS DEFINED
//get user input
void get_user_input(void)
{
    do
    {
        text = get_string("\nText: ");
    }
    while (text <= 0 || text[0] == '\0');
    //printf("\nFull string: %s\n", text); //debug use
}
//end get user input

//start word_count
int word_count(string txt)
{
    int txlen = strlen(txt);
    words = 0;
        for (x = 0; x<txlen; x++)
        {

        if ((txt[x - 1] == ' ' && txt[x] > 64 && txt[x] < 123 && txt[x + 1] == ' ') || (txt[x] > 64 && txt[x] < 123 && txt[x + 1] == ' ')
        || (txt[x - 1] > 64 && txt[x - 1] < 123 && txt[x] == '.') || (txt[x - 1] > 64 && txt[x - 1] < 123 && txt[x] == ',')
        || (txt[x - 1] > 64 && txt[x - 1] < 123 && txt[x] == '?')
        || /*(txt[x-1] > 64 && txt[x-1] < 123 && txt[x] == '\'') ||*/ (txt[x - 1] > 64 && txt[x - 1] < 123 && txt[x] == '!'))
        {
            //printf("[%c], ", txt[x]); //debugging output
            words++;
        }

        }
    return 0;

}
//end word_count

//start letter_count
int letter_count(string txt)
{
    int txlen = strlen(txt);
    letters=0;
    for (x = 0; x < txlen; x++)
    {
    if (txt[x] > 64 && txt[x] < 123 && txt[x] != 32 && txt[x] != '.' && txt[x] != '!' && txt[x] != '?' && txt[x] != ',' && txt[x] != '-')
    {
        if (txt[x] != ends[0] && txt[x] != ends[1] && txt[x] != ends[2])
        {
        letters++;
        }
    }
}
return 0;
}
//end letter_count

//start sentence_count
int sentence_count(string txt)
{
    int txlen = strlen(txt);
    for (x = 0; x < txlen; x++)
    {
    if ((txt[x - 3] > 64 && txt[x - 3] < 123 && txt[x - 2] > 64 && txt[x - 2] < 123 && txt[x - 1] > 64 && txt[x - 1] < 123 &&  txt[x] == '.')
    || (txt[x - 1] > 64 && txt[x - 1] < 123 && txt[x] == '?') || (txt[x - 1] > 64 && txt[x - 1] < 123 && txt[x] == '!'))
    {
        sentence++;
    }
}
return 0;
}
//end sentence_count

//start grade_calc
void grade_calc(string txt)
{
    /*
    L = the average number of letters per 100 words in the text
    S = the average number of sentences per 100 words in the text.
    */
    L = (((float)letters / words) * 100); //OMG FOREVER IT TOOK ME TO FIGURE THE (float)
    S = (((float)sentence / words) * 100); //I WILL NEVER FORGET THIS CASTING FLOAT BIZNES
    index = round((0.0588 * L) - (0.296 * S) - 15.8);
    //printf("letters: %i, sentences: %i, words: %i \n", letters, sentence, words); //debuggin output
    //printf("L: %f, S: %f, INDEX: %f \n", L, S, index); //debuggin output
    if (index < 1)
    { //lower than grade 1
        printf("Before Grade 1\n");
    }
    else if (index > 0.5 && index < 1.5)
    { //lower than grade 2
        printf("Grade 1\n");
    }
    else if (index >= 2 && index < 2.5)
    { //lower than grade 3
        printf("Grade 2\n");
    }
    else if (index >= 3 && index < 3.5)
    { //lower than grade 4
        printf("Grade 3\n");
    }
    else if (index >= 4 && index < 4.5)
    { //lower than grade 5
        printf("Grade 4\n");
    }
    else if (index >= 5 && index < 5.5)
    { //lower than grade 6
        printf("Grade 5\n");
    }
    else if (index >= 6 && index < 6.5)
    { //lower than grade 7
        printf("Grade 6\n");
    }
    else if (index >= 7 && index < 7.5)
    { //lower than grade 8
        printf("Grade 7\n");
    }
    else if (index >= 8 && index < 8.5)
    { //lower than grade 9
        printf("Grade 8\n");
    }
    else if (index >= 9 && index < 9.5)
    { //lower than grade 10
        printf("Grade 9\n");
    }
    else if (index >= 10 && index < 10.5)
    { //lower than grade 11
        printf("Grade 10\n");
    }
    else if (index >= 11 && index < 11.5)
    { //lower than grade 12
        printf("Grade 11\n");
    }
    else if (index >= 12 && index < 12.5)
    { //lower than grade 13
        printf("Grade 12\n");
    }
    else if (index > 13.5)
    { //above grade 12
        printf("Grade 16+\n");
    }
    //printf("Grade %i\n", (int)index); //debug output
}
//end grade_calc

//start output
void output_numbers(void)
{
    printf("%i letter(s) \n%i word(s) \n%i sentence(s) \n", letters, words, sentence); //keep this
}
//end output

/*
THE LIST OF KEYS WITH THEIR ASCII VALUES BELOW

    ###################################################
         CHARACTER KEY: 0        INTEGER VALUE: 48
         CHARACTER KEY: 1        INTEGER VALUE: 49
         CHARACTER KEY: 2        INTEGER VALUE: 50
         CHARACTER KEY: 3        INTEGER VALUE: 51
         CHARACTER KEY: 4        INTEGER VALUE: 52
         CHARACTER KEY: 5        INTEGER VALUE: 53
         CHARACTER KEY: 6        INTEGER VALUE: 54
         CHARACTER KEY: 7        INTEGER VALUE: 55
         CHARACTER KEY: 8        INTEGER VALUE: 56
         CHARACTER KEY: 9        INTEGER VALUE: 57
    ###################################################
         CHARACTER KEY: !        INTEGER VALUE: 33
         CHARACTER KEY: "        INTEGER VALUE: 34
         CHARACTER KEY: #        INTEGER VALUE: 35
         CHARACTER KEY: $        INTEGER VALUE: 36
         CHARACTER KEY: %        INTEGER VALUE: 37
         CHARACTER KEY: &        INTEGER VALUE: 38
         CHARACTER KEY: '        INTEGER VALUE: 39
         CHARACTER KEY: (        INTEGER VALUE: 40
         CHARACTER KEY: )        INTEGER VALUE: 41
         CHARACTER KEY: *        INTEGER VALUE: 42
         CHARACTER KEY: +        INTEGER VALUE: 43
         CHARACTER KEY: ,        INTEGER VALUE: 44
         CHARACTER KEY: -        INTEGER VALUE: 45
         CHARACTER KEY: .        INTEGER VALUE: 46
         CHARACTER KEY: /        INTEGER VALUE: 47
         CHARACTER KEY: :        INTEGER VALUE: 58
         CHARACTER KEY: ;        INTEGER VALUE: 59
         CHARACTER KEY: <        INTEGER VALUE: 60
         CHARACTER KEY: =        INTEGER VALUE: 61
         CHARACTER KEY: >        INTEGER VALUE: 62
         CHARACTER KEY: ?        INTEGER VALUE: 63
         CHARACTER KEY: @        INTEGER VALUE: 64
         CHARACTER KEY: {        INTEGER VALUE: 123
         CHARACTER KEY: |        INTEGER VALUE: 124
         CHARACTER KEY: }        INTEGER VALUE: 125
         CHARACTER KEY: ~        INTEGER VALUE: 126
##############################################################
         CHARACTER KEY: A, a     INTEGER VALUE: 65, 97
         CHARACTER KEY: B, b     INTEGER VALUE: 66, 98
         CHARACTER KEY: C, c     INTEGER VALUE: 67, 99
         CHARACTER KEY: D, d     INTEGER VALUE: 68, 100
         CHARACTER KEY: E, e     INTEGER VALUE: 69, 101
         CHARACTER KEY: F, f     INTEGER VALUE: 70, 102
         CHARACTER KEY: G, g     INTEGER VALUE: 71, 103
         CHARACTER KEY: H, h     INTEGER VALUE: 72, 104
         CHARACTER KEY: I, i     INTEGER VALUE: 73, 105
         CHARACTER KEY: J, j     INTEGER VALUE: 74, 106
         CHARACTER KEY: K, k     INTEGER VALUE: 75, 107
         CHARACTER KEY: L, l     INTEGER VALUE: 76, 108
         CHARACTER KEY: M, m     INTEGER VALUE: 77, 109
         CHARACTER KEY: N, n     INTEGER VALUE: 78, 110
         CHARACTER KEY: O, o     INTEGER VALUE: 79, 111
         CHARACTER KEY: P, p     INTEGER VALUE: 80, 112
         CHARACTER KEY: Q, q     INTEGER VALUE: 81, 113
         CHARACTER KEY: R, r     INTEGER VALUE: 82, 114
         CHARACTER KEY: S, s     INTEGER VALUE: 83, 115
         CHARACTER KEY: T, t     INTEGER VALUE: 84, 116
         CHARACTER KEY: U, u     INTEGER VALUE: 85, 117
         CHARACTER KEY: V, v     INTEGER VALUE: 86, 118
         CHARACTER KEY: W, w     INTEGER VALUE: 87, 119
         CHARACTER KEY: X, x     INTEGER VALUE: 88, 120
         CHARACTER KEY: Y, y     INTEGER VALUE: 89, 121
         CHARACTER KEY: Z, z     INTEGER VALUE: 90, 122
*/