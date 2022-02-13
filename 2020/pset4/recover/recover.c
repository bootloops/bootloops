#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
//MAIN
int main(int argc, char *argv[])
{
    FILE *in_file = fopen(argv[1], "r");
    if (argc != 2) //check
    {
        //print error
        printf("[ERROR:1]\n\t Usage: ./recover <filename.datatype> \n");
        return 1;
        exit(1);
    }
    else if (!in_file)
    {
        //file error
        printf("[ERROR:2]\n\t File could not be read");
        return 1;
        exit(1);
    }
    else
    {
        //do recovery
        FILE *image = NULL;

        BYTE *buffer = malloc(512);             //set buffer of bytes - free me
        char *jpeg_file = malloc(8);            //filenames           - free me

        int file_count = 0;
        int writing = 0;

        sprintf(jpeg_file, "%03i.jpg", file_count);
        image = fopen(jpeg_file, "w");

        while (fread(buffer, 512, 1, in_file) && !feof(in_file))
        {
            //if find jpeg header
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
            {
                if (file_count == 0) //0 files initialized, so not already writing.
                {
                    fwrite(buffer, 512, 1, image);  //start writing
                    file_count++;                   //count files found
                    writing = 1;                    //now is writing
                }
                else
                {
                    fclose(image);                              //if when filecount is more than 0
                    sprintf(jpeg_file, "%03i.jpg", file_count); //print string into jpeg_file, "file_count.jpg"
                    image = fopen(jpeg_file, "w");              //open new file for writing, "file_count.jpg" (assigned to jpeg_file) -> write
                    fwrite(buffer, 512, 1, image);              //write whats in the buffer, to the new image
                    file_count++;                               //add to file_count
                }
            }
            //if not find jpeg header sequence & already writing
            else if (writing)
            {
                fwrite(buffer, 512, 1, image); //keep writing what is in the buffer to new image
            }
        } //END WHILE

        //close everything & free the people!
        fclose(in_file);
        fclose(image);
        free(buffer);
        free(jpeg_file);
        return 0;

    }   //END FIRST ELSE
}//END MAIN

