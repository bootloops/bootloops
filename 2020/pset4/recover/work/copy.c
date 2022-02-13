#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>



typedef uint8_t BYTE;

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

    bool end = false;

    BYTE *buffer = malloc(512 * sizeof(BYTE));

    int fileNo = 0;

    while(!end)
    {

        if(fread(buffer, 1, 512, file) != 512)
        {

            end = true;
            break;

        }

        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {

            char *fileName = malloc(sizeof(int) * 7);
            sprintf(fileName, "%03i.jpg", fileNo);
            FILE *image = fopen(fileName, "w");
            do
            {
                fwrite(buffer, 1, 512, image);
                fread(buffer, 1, 512, file);
            }
            while(!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0)));
            fileNo++;

        }

    }

}