#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>


//STRINGS
string plaintext;

string useage = "Useage: ./caesar argument";
string hint = "[use a positive integer]";
string only = "[use only POSITIVE integer]";

//FUNCTIONS
void get_plaintext(void);
int encipher(string ptx);
int check_args(int c, string s);

//INTS
int K;


//MAIN
int main(int arg_count, char *arg_string_array[])
{
    if (arg_count == 2 )
    {
        //printf("ARGS: %s\n", arg_string_array[1]); //debuggin
        check_args(arg_count, arg_string_array[1]);
        return 0;
    }
    else
    {
        //printf("ARGS: %s\n", arg_string_array[1]); //debugging
        printf("%s %s\n", useage, hint);
        return 1;
    }
    return 1;
}

//FUNCTIONS DEFINED
//start check_args
int check_args(int c, string s) //WORKING NO PROBLEM
{

    int z = strlen(s); //string length
    for (int i = 0; i < z; i++) //for loop i (length of arg)
    {
        int p = s[i]; //assign p to each char in argstring
        int a = s[i+1]; //assign a to each char+1 in argstring for ensuring we can keep char '0'(zero) as entered, only after a positive interger (eg. 10, ok. 01, not ok.)
        //check argstring for characters
        /*below is define as:
            if arg[char] is outside range of ascii number 0
            or arg[char] is inside range of capital ascii chars
            or arg[char] is inside range of lowercase ascii chars
                then; false, print error.
            else if arg[char] is within range of numbers 0 - 9 ascii values
            AND arg[char+1] is the '\0' placeholder?null char?
                then; true, get plaintext and encipher it;

            found a flaw that check50 did not detect/check -- if you enter positive integer, then a 0.
            the program fails. which it should not. as per check50 i would assume all is good, and submit50
            but, i found this flaw and so i feel its not working quite right
            and so I am fixing it somehow... to be continued.

        */
        if ((p < 49 || p > 57) || (p >= 65 && p <= 90) || (p >= 97 && p <= 122))
        //be sure its not, p <= 48... as that cancels out the next else
        //if i enter 0 as a char, i want to keep it, but only after a positive integer has been entered first
        {
            //false numbers
            //printf("False: %c\n", p);
            printf("Error: %s %s\n", useage, only);
            exit(1);
            return 1;
        }
        else if (((p > 48 && p <= 57) && (a >= 48 && a <= 57)) || (s[i+1] == '\0'))
        //no chars, only numbers and '\0' or no chars, only numbers including 0.
        /*
        else if (((p > 48 && p <= 57) && (s[i+1] == '\0')) || ((p > 48 && p <= 57) && (a >= 48 && a <= 57)) || (s[i+1] == '\0'))
        the above was very peculiary to figure out, but it now works as expected.
        a user can now enter 10, or, 100 or 200000 or whatever they choose.

        now that is solved, I found another error that quite possibly will be undetected by check50 as well
        but perhaps this is not necesarry for the assignment? still i beleive it's not working correctly;

        the equation below i use to figure the rotational values, unfortunately has the flaw.
        I need to ensure i am within a value of 1-26 in order to adjust the char values from plaintext,
        into correct char values, maintaining case and not allowing anything else.

        right now, without modifying the equation, if a user were to input a value at say
        2000, as key. the cipher output is all over the place, which I thought i ensured was not allowed.

        What i realised, is, I didnt really put a check in place to ensure the equation returned value is
        within the range of modifiable characters. (26) So to adjust that, i include another if statement,
        to reduce the larger numbers down, really as per the check50 I only needed to do this if reducer
        for the lowercase values, as
                *check50 doesnt check BARFOO with a key of 65 -- that could detect this problem maybe
        */
        {

            //true numbers
            //printf("True: %c\n", p);
            K = atoi(s); //must not assign to s[char] use the entire 's' string -- checks are complete, this should be fine.
            get_plaintext();
            encipher(plaintext);
            return 0;
        }
    }
    printf("\n");


    return 1;
}
//end check_args

//start get_plaintext
void get_plaintext(void) //WORKING NO PROBLEM
{
    do
    {
        plaintext = get_string("\nplaintext: ");
    }
    while (plaintext[0] == '\0'); //if plaintext first char null, repeat

}
//end get_plaintext

//start encipher
int encipher(string ptx) //PROBLEM -- not rotating letters
{

    int ctx_len = strlen(ptx); //ctx_len is the length of plaintext
    char C[ctx_len]; //easier to type - plaintext copy into char C array
    printf("\nciphertext: "); //header of ciphertext
    for (int x = 0; x < ctx_len; x++)  //increment x until read full length of plaintext
    {
        //check spaces
        if (ptx[x] == 32) {
            //printf("Space[%c]\n", ciphertext[x]); //debugging output
            C[x] = ptx[x];
            printf("%c", C[x]); //turn on
        }
        //check numbers
        if (ptx[x] >= 48 && ptx[x] <= 59) {
            //printf("Numbers[%c]\n", ciphertext[x]); //debugging output
            C[x] = ptx[x];
            printf("%c", C[x]); //turn on
        }
        //check punctuations
        if ((ptx[x] >= 33 && ptx[x] <= 47) || (ptx[x] >= 58 && ptx[x] <= 64) || (ptx[x] >= 123 && ptx[x] <= 127)) {
            //printf("Punctuations[%c]\n", ciphertext[x]); //debugging output
            C[x] = ptx[x];
            printf("%c", C[x]); //turn on
        }
        //check letters -- rotate letters (this is the magic)
        else if (ptx[x] >= 65 && ptx[x] <= 90) //CAPITAL LETTERS ASCII VALUE
        {
            C[x] = ptx[x] + K; //cipher char will be plaintext char + K

            if (C[x] > 90 || C[x] <= 0) //90 is out of range of ascii capital letters
            {
                //printf("OutRange: \n\t%c", C[x]); //debugging
                C[x] = (ptx[x] + K) % 90;
                if (C[x] > 26)
                {
                    int C2 = C[x] % 26;
                    //printf("C[x] = %i\n", C2); //debugging
                    C2 = 65 + C2 - 1;
                    printf("%c", C2);
                    //printf("CHAR[x] = %i\n", C2); //debugging
                    //printf("\nValue C[x]: %i\n", C[x]); //debugging
                    //printf("Char C[x]: %c\n", C[x]); //debugging

                }
                else
                {
                //printf("\n[OR1,Calc: %c]\n", C[x]); //debugging
                char C2 = 65 + C[x] - 1;

                //printf("\n[OR2,Calc: %c]\n", C2); //debugging
                C[x] = C2;
                //printf("\n[OR3,Calc: %c]\n", C[x]); //debugging
                printf("%c", C[x]); //turn on
                }
            }
            else
            {
                printf("%c", C[x]); //turn on
                //printf("InRange: \n\t%c\n", C[x]);
                //C[x] = ptx[x];
            }
        }
        else if (ptx[x] >= 97 && ptx[x] <= 122) //LOWERCASE ASCII VALUES
        {
            C[x] = ptx[x] + K;
            /* Another mysterious beast has presented itself to me, and drove me crazy!
            But alas, I fought through day and night crunching ascii and come to the AH HA! moment.
            I wrote an external program, scrap.c, and use it to print out lowercase w + 13,
            I got a space & or a new line? whatever it was, was not right.
            After getting compiler error on scrap.c first compile, indicating assigning char value of
            132 is out of the scope of 127, therefore became -124 somehow ^_^ ?? memory games i suppose...
            anyhow, what I had to do is add the '|| C[x] <= 0' statement to the IF below
            */
            if (C[x] > 122 || C[x] <= 0)
            {
                //printf("OutRange: \n\t%c", C[x]); //debugging
                C[x] = (ptx[x] + K) % 122;
                if (C[x] > 26)
                {
                    int C2 = C[x] % 26;
                    //printf("C[x] = %i\n", C2); //debugging
                    C2 = 97 + C2 - 1;
                    printf("%c", C2);
                    //printf("CHAR[x] = %i\n", C2); //debugging
                    //printf("\nValue C[x]: %i\n", C[x]); //debugging
                    //printf("Char C[x]: %c\n", C[x]); //debugging

                }
                else
                {
                //printf("\n[OR1,Calc: %c]\n", C[x]); //debugging
                char C2 = 97 + C[x] - 1;
                //printf("\n[OR2,Calc: %c]\n", C2); //debugging
                C[x] = C2;
                //printf("\n[OR3,Calc: %c]\n", C[x]); //debugging
                printf("%c", C[x]); //turn on
                }
            }
            else
            {
                printf("%c", C[x]); //turn on
                //printf("InRange: \n\t%c\n", C[x]);
                //C[x] = ptx[x];
            }
        }

    }
    //newline cleanup
    printf("\n");
    return 0;
}
//end encipher
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