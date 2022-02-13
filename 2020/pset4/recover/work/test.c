#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>



//typedef uint8_t BYTE;
const int MAX = 2048;


int main(int argc, char *argv[])
{

    // Check usage
    if (argc != 2)
    {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("invalid file");
        return 1;
    }

    //CHECK PASS
    //NEWVARS

    unsigned char buffer[MAX]; //=malloc(512 * sizeof(BYTE));
    int fileNo = 0;
    char *fileName = malloc(sizeof(int) * 7);
    FILE *image ;


    //START READ
    while(!feof(file))
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            image = fopen(fileName, "w");
            sprintf(fileName, "%03i.jpg", fileNo);
            fwrite(buffer, 1, 512, image);
            fread(buffer, 1, 512, file);
            fileNo++;
        }
        else
        {
            continue;
        }


    }

}