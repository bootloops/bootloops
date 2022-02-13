#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Check args, for 2 words
    if (argc != 2)
    {
        printf("Need 1 arguments! <filename>\n");
        return 1;
    }

    //Opened file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("No file to open! <Did you enter a correct file name?\n");
        return 1;
    }

    //Read 4 bytes from file, 32bits. [1byte = 8bits.]
    FILE *new_file = NULL; //initiate placeholder for new file to be written in
    BYTE *bytes = malloc(32); //using malloc to give space to store bytes

    int read = 0;
    int is_jpg = 0;
    int not_jpg_header = 0;
    int line_arr[5] = {};
    int line = 0;
    int line_num = 0;
    char *found_header_line = NULL;
    int found_line_num = 0;
    while (fread(bytes, 512, 1, file) && !feof(file))
    {
        read++; //reading bytes, 512, 1, from *file

        //printf("%x", *bytes); //enable for seeing the action!
        if (read == 4) {
            //printf(" ");      //enable for seeing the action!
            read = 0;
            line++;
            if (line == 8) {
                //printf("\n"); //enable for seeing the action!
                line_num += line;
                line = 0;
            }
        }
        //Check if bytes are 0xff, 0xd8, 0xff, 0xe0 -- starting point of most jpeg
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && ((bytes[3] & 0xf0) == 0xe0))
        {
            is_jpg += 1;
            line_arr[0] = line_num;
            line_arr[1] = bytes[0];
            line_arr[2] = bytes[1];
            line_arr[3] = bytes[2];
            line_arr[4] = bytes[3];

            //printf("Header found here:\n line %i: \t%x %x %x %x\n\n", line_num, bytes[0], bytes[1], bytes[2], bytes[3]);

        }
        else
        {
            not_jpg_header += 1;
            //printf("Not a jpeg\n");
        }


    }
    //fclose(file);
    printf("\n"); //clean output


    for (int p = 0; p < 5; p++) {
        ((((line_arr[p+1] == 0)) && printf("not_jpg = %i, Non jpeg header\n", not_jpg_header)) ||
        (((p == 0)) && printf("Line num: %i || ", line_arr[p])) || printf("%x, ", line_arr[p]));
    }
    printf("\n");

    ((is_jpg > 0)) && printf("is_jpg = %i, Found jpeg header\n", is_jpg);



}