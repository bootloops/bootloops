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

    BYTE *buffer = malloc(2048 * sizeof(BYTE));

    int img_count = 0;

    while(fread(buffer, 1, 512, file))
    {
        if(!feof(file) && (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0)))
        {
            for (int a = 0; a < sizeof(*buffer); a++)
            {
                char *fileName = malloc(sizeof(int) * 7);
                sprintf(fileName, "%03i.jpg", img_count);
                FILE *image = fopen(fileName, "w");
                fwrite(buffer, 1, 512, image);
                fread(buffer, 1, 512, file);
                //do
                // while(!feof(file))
                // {
                //     fwrite(buffer, 1, 512, image);
                //     fread(buffer, 1, 512, file);
                // }
                //while(!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0)));

            }
            img_count++; //if not eof and matches 4 bytes, count +1
        }

    }

}