#include <stdio.h>
#include <cs50.h>


void get_positive(void);
void build_blocks(int n);

int main(void)
{
    //intro
    printf("\t\nLets build a half pyramid!\n\t");
    //call function to get postiive int, and return build a half-pyramid
    get_positive();


}


//define functions

//get positive int function
void get_positive(void)
{
    //line up variables
    int size;

    //while less than 1, do --- see below
    do {
    size = get_int("Height(1-8): ");
    }
    while (size <= 0 || size > 8); //-----------^
        ///OMG i spent hours trying to peice this thing together!
        //always remember to be as literal as possible, [size <*=* 0] lessthan equal. not just lessthan.
    //if the input is greater than 1 & less than 8, output back to user
    if (size > 0 && size < 9)
    {
        build_blocks(size);
    }

}

//build blocks from positive int
void build_blocks(int n)
{
    string space = " "; //experiment purpose
    int d, i, c;


    for (i = 0; i < n; i++)
    {                               // d = **(n-1)** because, we need to deduct from that space on the line
                                    // thats what caused all those red errors about extra spaces <X_X>
        for (d = (n-1); d > i; d--) // this I was too busy looking at the next for loop below
        {
        //printf("%s", space);  //this didnt work, it was the ABOVE notes** that solved it.
        printf(" ");
        }
        for (c = -1; c < i; c++)
        {
        printf("#");
        }

      printf("\n");
    }
}