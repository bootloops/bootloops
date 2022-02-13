#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Check args, for 2 words
    if (argc != 2)
    {
        return 1;
    }

    //Opened file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    //Read 3 bytes from file, 24bits. 1byte = 8bits.
    unsigned char bytes[3]; //unsigned is because this array is larger than -127 to 127
    fread(bytes, 3, 1, file);

    //Check if bytes are 0xff, 0xd8, 0xff -- starting point of most jpeg
    if ((bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff) && ((bytes[3] & 0xff) == 0xe0))
    {
        printf("Maybe jpeg\n");
    }
    else
    {
        printf("Not a jpeg\n");
    }
}