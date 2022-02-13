#include <stdio.h>
#include <stdlib.h>
#include <string.h> //using strlen()
#include <unistd.h> //using sleep()
#include <ctype.h> //if need to use toupper() / tolower()
#include <cs50.h> //get_string()

void generate_hex_to_decimal(int hex[]);
void store_in_file();
void get_it();
void scanner_f();
void copy_func();
void noswap(int a, int b); //does not actually swap
void swap(int *a, int *b); //actually swaps
float mather(int n);
void dotter();

int main(void)
{
    //play with functions
    int HEX[8][8] = {
        {0xFF, 0xD8, 0xfe, 0x00, 0xC4, 0x08, 0xf3, 0x45},
        {0xFF, 0xD8, 0xee, 0x00, 0x14, 0x08, 0xf3, 0x45},
        {0xFF, 0xD8, 0xae, 0xf0, 0xA4, 0xe8, 0xf6, 0x25},
        {0xFF, 0xD8, 0xfe, 0x00, 0xC4, 0x08, 0xf3, 0x45},
        {0xFF, 0xc8, 0x1e, 0x02, 0xCf, 0xe8, 0xf3, 0x45},
        {0xFF, 0xD8, 0xfe, 0x00, 0xC4, 0x08, 0xf3, 0x45},
        {0xFF, 0xD8, 0xfe, 0x00, 0xC4, 0x08, 0xf3, 0x45},
        {0xFF, 0xD8, 0xfe, 0x00, 0xC4, 0x08, 0xf3, 0x45}
    };

    for (int i = 0; i < 8; i++)
    {
        generate_hex_to_decimal(HEX[i]);
    }
    printf("\n\n\n");
    get_it();
    /*
    int a = 1;
    int b = 2;
    printf("a: %i b: %i\n", a, b);
    swap(&a, &b);
    printf("a: %i b: %i\n", a, b);
    copy_func();
    */
}

//functions

void generate_hex_to_decimal(int hex[]) {
    int x = 0, y = 0;
    int new_pixel = 0;
    int new_pixel_avg = 0;
    for (int i = 0; i < 8; i++)
    {
        x++;
        printf("%i \t %i ", x, hex[i]);
        new_pixel = new_pixel + hex[i];
        new_pixel_avg = (new_pixel / 8);
    }
    printf("\n");
    printf(" [NEW: %i] ", new_pixel);
    printf(" [NEW_AVG: %i] ", new_pixel_avg);

}//end hex gen


void store_in_file()
{
    //pointer to FILE, called file.
    //fopen opens first argument file, 2nd arg, r,w,a -- a=append, r=read, w=write;
    FILE *file = fopen("phonebook.csv", "a");

    //some char vars
    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    //write strings to file
    fprintf(file, "%s,%s\n", name, number);

    //close file
    fclose(file);

}


void copy_func()
{
    //copying vars
    char *s = get_string("s: "); //prompt for string, using cs50.h <get_string>

    char *t = malloc(strlen(s) + 1); //+1 is to include the '\0' char -- setting t to the size of s

    int N = strlen(s); //set N to length of s

    for (int i = 0; i <= N; i++) //copy t into s
    {
        t[i] = s[i];
    }
    for (int z = 0; z <= N; z++) //change to "Capital space Capital"
    {
        if (s[z] == 32)
        {
            s[z+1] = toupper(s[z+1]);
            //printf("%c", s[z]);
        }
    }
    s[0] = toupper(s[0]);

    printf("%s\n", s);
}


void scanner_f() //not working
{
    char *s = "none";
    printf("s: ");
    scanf("%s", (char*)s); //string scan
    for (int i = 0; i < strlen(s); i++)
    {
        printf("s: %c\n", s[i]);
    }

}

void get_it() //constant segmentation faults...
{
    char *x;
    printf("x: ");
    //no error checking built in to scanf
    scanf("%s", &x); //check users prompt
    printf("x input: %c\n", *x);
}
void noswap(int a, int b)
{
    int x = a;
    b = a;
    a = x;
}
void swap(int *a, int *b)
{
    int x = *a;
    *b = *a;
    *a = x;
}


float mather(int n)
{
    float x = ((n * 2) / 5);
    printf("%f", x);
    return x;
}

void dotter()
{
    char *dotter = ".";
    int num = 1000;
    for (int i = 0; i < num; i++)
    {
        printf("%s", dotter);
        sleep(mather(2));
    }
    printf("\n");
}