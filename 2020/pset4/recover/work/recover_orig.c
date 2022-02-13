#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// void CGREAD_INTO_BUFFER(FILE* rcvr, int chunk_r);
int FIND_JPEG(int bufchk[]);

//BUFFER PROPS
const int chunk = 512;
const int MAX_BUFF = 2048;
int buffer[MAX_BUFF];

//FILE PROPS
FILE* recover_me;

//COUNTERS
int imgcount = 0, start_count = 0, end_count = 0;

//MAIN
int main(int argc, char *argv[])
{
//CHECK VALID
    if (argc < 2) //check enough args
    {
        printf("ERROR(-1): Not enough arguments. \n\t [ Usage: ./recover <filename.datatype> ]\n");
        return -1;
        exit(-1);
    }
    else
    {
    recover_me = fopen(argv[1], "r"); //check if infile is valid
        if (!recover_me)
        {
            printf("ERROR(-2): Invalid input file.\n [ Usage: ./recover <filename.datatype>\n");
            return -2;
            exit(-2);
        }
        else //valid file -- pass it around
        {
            int a = 0;
            //variables for use in functions
            while(fread(buffer, chunk, 1, recover_me))
            {
                if (a <= chunk) {
                    a++; //count for to 512, start at 0.

                }
                else
                {
                    a = 0; //if reach 512, set to 0
                }
                if (!feof(recover_me))
                {
                    //printf("0x%x \n", buffer[a]);
                    unsigned char bytes[4];
                    //Check if bytes are 0xff, 0xd8, 0xff -- starting point of most jpeg
                    while(fread(bytes, 4, 1, recover_me))
                    {
                    if ((bytes[0] == 0xff) && (bytes[1] == 0xd8) && (bytes[2] == 0xff) && ((bytes[3] & 0xff) == 0xe0))
                    {
                        imgcount++;
                        printf("image count: %i", imgcount);
                    }
                    else
                    {

                    }
                    }

                }
            }
            //CGREAD_INTO_BUFFER(recover_me, chunk);

            return 0; //complete successfull

        }


    }
    return -3; //complete with error unknown

}


// void CGREAD_INTO_BUFFER(FILE* rcvr, int chunk_r)
// {
//     //fread(<buffer>, <size>, <qty>, <ptr>)
//     int e = 0;
//     while(fread(buffer, chunk_r, 1, rcvr)) //while reading into buffer
//     {
//         read_count++;
//         if (feof(rcvr))
//         {
//             exit(0);
//         }
//             int r, g, b, a;
//             r = buffer[e], g = buffer[e+1], b = buffer[e+2], a = buffer[e+3];
//             if (r == 0xff && g == 0xd8 && b == 0xff && ((a & 0xf0) == 0xe0))
//             {
//                 //if match start jpg file (start)
//                 imgfound_start++; //count start of jpgs
//                 //start new jpg

//                     //printf("%i \n", imgfound); //debug
//                     //printf("[R] 0x%x | [G] 0x%x | [B] 0x%x | [A] 0x%x \n", r, g, b, a); //debug
//                 if (chunk - r == 0xff && chunk - g == 0xd8 && chunk - b == 0xff && ((chunk - a & 0xf0) == 0xe0))
//                 {
//                     //if match end jpg file (end)
//                     imgfound_end++; //count end of jpgs
//                     //close jpg
//                 }

//             }
//             else
//             {
//                 //keep  printing to jpgfile


//             }


//         e++;
//     }
//     printf("Img start: %i \nImg end: %i", imgfound_start, imgfound_end);

// }


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
    OPEN MEM CARD
        REPEAT UNTIL END OF CARD:
            READ 512 BYTES INTO BUFFER
             CHECK BUFFER FOR:
                IF FOUND JPEG
                    IF FIRST JPG
                        ..FOPEN NEW JPG000.JPG
                    ELSE
                        ..FCLOSE NEW JPG000.JPG
                ELSE
                    IF ALREADY FOUND JPG
                        ..KEEP WRITING TO THAT JPG###.JPG
    CLOSE ANY REMAINING FILES

            close file //close

//create a counter for which image I am copying to or which image I am on

//allocate memory for a string which will hold the outfile names

//create an array of file pointers

//name the first outfile

//open a while loop

//read the 512 bytes

//if the first image has not yet been located don't do anything

//iterate

//read another 512 bytes and repeat until first image found

//start to write 512 bytes to the image every iteration

//if you reach the next jpeg close the previous one and increase the counter for which jpg we're on

//open the next file and start writing to it

//keep repeating the process until you reach the end of the file and then break the loop

*/