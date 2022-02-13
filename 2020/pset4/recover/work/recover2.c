#include <stdio.h>
#include <stdlib.h>

int check_infile(int argc, char *argv[]);
void cgread_file(FILE* rcvr);
int start_end(int buff);

int main(int argc, char *argv[])
{
    //REMEMBER THAT THE IMAGES ARE STORED BACKWARDS.. i think.
    //after printing out the hex into a file and grepping thru it
    //i found that e*ffd8ff is the representation,
    // not ffd8ffe*

// block = 512bytes
// 8 bit = 1 byte
//jpges "always" starts 1st byte=0xff  2nd byte=0xd8  3rd byte=0xff 4th byte=0xe*
//bitwise shorthand
// (block[0][1] & 0xf0) == 0xe0;

//working with file pointers
//fopen(), fclose(), fread(), fgetc(), fputc(), fwrite();
//char ch = fgetc(filename); cant read if in write mode.
/* PSEUDO
    Open mem card
        repeat until end of card:
            read 512 bytes, per block, into a buffer
            if start of new JPEG
                if first JPG
                    open new file, write hex to it
                    found-image.jpg //prev-found-image
                else
                    close prev-found-image.jpg //close prev-found-image
                    open new-image.jpg //start new-image.jpg
            else
                end of JPG
                    close file //close
*/
    // Check for invalid usage
    if (argc < 2)
    {
        printf("ERROR(-1): Not enough arguments. \n\t [ Usage: ./recover <filename.datatype> ]\n");
        return 1;
        exit(1);
    }
    else
    {
        for (int t = 1; t < argc; t++)
        {
            FILE* recover_me = fopen(argv[t], "r"); //test if we can open the infile for read
            if (!recover_me)
            {
                printf("ERROR(-2): Invalid input file.\n [ Usage: ./recover <filename.datatype>\n");
                return -1;
                exit(-1);
            }
            else
            {
                cgread_file(recover_me);
                return 0;
                //read the file
            }
                return 0;
                //read the file
        }
    }

    return 1;
}

void cgread_file(FILE* rcvr)
{
    FILE* recover_me = rcvr;
    unsigned long data = 8; //i think this means 8 bites, 1 byte [R=2, G=2, B=2, '\0'=2]=8
    int block = 512;
    int buffer[2048];
    int count = 0;
    printf("File Data: \n");
    while(fread(buffer, data+1, block, recover_me))
    {
        for (int b = 0; b <= block; b++)
        {
            if (start_end(buffer[b]))
            {
                printf("0x%0x ", buffer[b]);
            }

             printf("0x%0x ", buffer[b]);
             count++;
        }
    count++;

    }
    printf("Total: %i\n", count);
}

void cgwrite_file(char argv[])
{
    //todo

}

int start_end(int buff)
{
    if ((buff == 0xff) || (buff == 0xd8) || (buff == 0xff))
    {
        return 1; //true
    }
    else
    {
        return 0; //false
    }
    return 0;
}