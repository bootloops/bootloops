#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        FILE* file = fopen(argv[1], "r");
        int JPEGcounter = 0;
        BYTE* buffer = malloc(512);
        char names[8];

        while(fread(buffer, 512, 1, file) == 1)
        {
            FILE* img = NULL;

            if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
            {
                sprintf(names, "%03i.jpg", JPEGcounter);
                img = fopen(names, "w");
                fwrite(buffer, 512, 1, img);
                JPEGcounter++;
            }
            else
            {
                fwrite(buffer, 512, 1, img);
            }
        }
        return 0;
    }
    else
    {
        printf("one command-line argument only\n");
        return 1;
    }
}