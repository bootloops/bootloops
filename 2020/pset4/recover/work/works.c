

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //incorrect usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //file cant be
    else
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("File could not be opened\n");
            return 1;
        }
        else
        {
            //READ FILE
            //an editable filename
            char *filename = malloc(8);

            //a buffer to read to
            unsigned char *buffer = malloc(512);
            int start = 0;
            int filenumber = 0;
            sprintf(filename, "%03i.jpg", filenumber);
            FILE *img = fopen(filename, "w");

            while (!feof(file))
            {
                if (fread(buffer, 512, 1, file))
                {
                    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                    {
                        //when first jpeg found
                        if (filenumber == 0)
                        {
                            fwrite(buffer, 512, 1, img);
                            filenumber++;
                            start = 1;
                        }
                        //start of every jpeg after first
                        else
                        {
                            fclose(img);
                            sprintf(filename, "%03i.jpg", filenumber);
                            img = fopen(filename, "w");
                            fwrite(buffer, 512, 1, img);
                            filenumber++;
                        }
                    }
                    //middle of jpeg
                    else if (start == 1)
                    {
                        fwrite(buffer, 512, 1, img);
                    }
                }
                //After reading an incomplete set of 512 bytes
                else
                {
                    //CLOSE AND FREE
                    fclose(file);
                    fclose(img);
                    free(buffer);
                    free(filename);
                    return 0;

                }
            }
        }
    }
}

