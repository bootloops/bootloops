#include "helpers.h"
#include <math.h>
#include <stdio.h> //debugging with printf
#include <stdlib.h>
#include <string.h>
int max(int s);
/*
NOTE TO SELF
<string.h> #library contains these functions
strlen() - get length of a string
strcat() - merge two strings
strcpy() - copy one string to another
strlwr() - convert string to lower case
strupr() - conver string to upper case
strrev() - reverse string
strcmp() - compare two strings

*/

// Convert image to grayscale //COMPLETED DO NOT TOUCH
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *temp = NULL;

    int row = height;
    int col = width;
    float avr_sum;
    int sumRed, sumGreen, sumBlue;
    int count = 0;
    int gscale;
    
    for (int y = 0; y < row; y++) //scroll from row0 to row[width-1] (up to down)
    {
        for (int i = 0; i < col; i++) //scroll from col0 to col[width-1] (left to right)
        {
            //define temp pointer
            temp = &image[y][i];
                //add all values together and divide by the total sum of the row
            avr_sum = round((image[y][i].rgbtRed + image[y][i].rgbtGreen + image[y][i].rgbtBlue) / 3.0);
            gscale = avr_sum;
                //set new colors
            temp->rgbtRed = gscale;
            temp->rgbtGreen = gscale;
            temp->rgbtBlue = gscale;
        }
    }
/*
    if RGB = 0,0,0 == black
    if RGB = 255,255,255 == white
    if RGB = 50,50,50 == light-gray
    if RGB = 150,150,150 == med-gray
    if RGB = 200,200,200 == dark-gray

    calculate the average of RGB values, use that as the new value for RGB
    if R = 50, G = 190, B = 90:
     avg = (50 + 190 + 90) / 3;
     average = 110
     new RGB = 110,110,110
     result is shade of gray that closely match original pixel
     must be INT, even if return FLOAT -- round():
    do it for the entire image, with a loop
    use a 2D array.
    for each pixel, calculate the average pixel value
     --set each color value to the average (make sure to round())
     ./filter -g infile.* outfile.* [to test if grayscale is succesfful]
*/
    return;
}

// Convert image to sepia //COMPLETE DO NOT TOUCH :)
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int row = height;
    int col = width;
    float sepiaRed, sepiaGreen, sepiaBlue;
    int sepRed, sepGreen, sepBlue;
    int array[3], sepia;

    for (int y = 0; y < row; y++) //scroll from row0 to row[width-1] (up to down)
    {
        for (int i = 0; i < col; i++) //scroll from col0 to col[width-1] (left to right)
        {

            //sepia formula
            sepiaRed = (.393 * image[y][i].rgbtRed) + (.769 * image[y][i].rgbtGreen) + (.189 * image[y][i].rgbtBlue);
            sepiaGreen = (.349 * image[y][i].rgbtRed) + (.686 * image[y][i].rgbtGreen) + (.168 * image[y][i].rgbtBlue);
            sepiaBlue = (.272 * image[y][i].rgbtRed) + (.534 * image[y][i].rgbtGreen) + (.131 * image[y][i].rgbtBlue);

            //set sepia INT
            array[0] = sepiaRed = round(sepiaRed);
            array[1] = sepiaGreen = round(sepiaGreen);
            array[2] = sepiaBlue = round(sepiaBlue);


            //use a function, pass it's values
            for (int x = 0; x < 3; x++)
            {
                if (max(array[x])) {
                    array[x] = 255;
                }
            }
            //set new colors
            image[y][i].rgbtRed = array[0];
            image[y][i].rgbtGreen = array[1];
            image[y][i].rgbtBlue = array[2];
            // //if values above 255, set max at 255.
            // if (sepiaRed > 255)
            // {
            //     sepiaRed = 255;
            // }
            // if (sepiaGreen > 255)
            // {
            //     sepiaGreen = 255;
            // }
            // if (sepiaBlue > 255)
            // {
            //     sepiaBlue = 255;
            // }

        }

    }

    //take BMP convert to SEPIA
    //reddish old-town feel

    //SERPIA FORMULA
    /*

                    [IF SCALE BELOW]
        sepiaRed = .393 * originalRed
                 + .769 * originalGreen
                 + .189 * originalBlue

        sepiaGreen = .349 * originalRed
                   + .686 * originalGreen
                   + .168 * originalBlue

        sepiaBlue = .272 * originalRed
                  + .534 * originalGreen
                  + .131 * originalBlue

        every value will return FLOAT, round() to whole to make an INT
        remember to CAP VALUES at 255.

    //Calculate each new color value using sepia formula

    //ensure the result is int between 0 and 255

    //test with ./filter -s infile.* outfile.*


    */

    return;
}


// Reflect image horizontally // COMPLETE DO NOT TOUCH :)
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if ( height > 0 )
    {
        RGBTRIPLE oswap[height][width];
        int max_col = width;
        int max_row = height;
        for (int z = 0; z < max_row; z++) //row
        {
            for (int i = 0; i < max_col; i++) //column
            {
                oswap[z][i].rgbtRed = image[z][i].rgbtRed;
                oswap[z][i].rgbtGreen = image[z][i].rgbtGreen;
                oswap[z][i].rgbtBlue = image[z][i].rgbtBlue;
            }
            for (int i = 0; i < max_col; i++) //column
            {
                int x = (width - 1) - i;
                image[z][i].rgbtRed = oswap[z][x].rgbtRed;
                image[z][i].rgbtGreen = oswap[z][x].rgbtGreen;
                image[z][i].rgbtBlue = oswap[z][x].rgbtBlue;
            }
        }
    }
    else
    {
        RGBTRIPLE oswap[height][width];
        int max_col = width;
        int max_height = height;
        for (int i = 0, z = height; i < max_col; i++) //column
        {

            oswap[z][i].rgbtRed = image[z][i].rgbtRed;
            oswap[z][i].rgbtGreen = image[z][i].rgbtGreen;
            oswap[z][i].rgbtBlue = image[z][i].rgbtBlue;
        }
        for (int i = 0, z = height; i < max_col; i++) //column
        {
            int x = (width - 1) - i;
            image[z][i].rgbtRed = oswap[z][x].rgbtRed;
            image[z][i].rgbtGreen = oswap[z][x].rgbtGreen;
            image[z][i].rgbtBlue = oswap[z][x].rgbtBlue;
        }
    }
    //MIRROR THE IMAGE
    //make all the items in the 2D array, and rearrange them so they are backwards

    //for each row, swap pixels horizontally
    // apply to each row until end with a loop

    //test with ./filter -r infile.* outfile.*

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //temp rgbt
    RGBTRIPLE temp[height][width];
	RGBTRIPLE *tmp;
	RGBTRIPLE *img;


    // For loop to set the value of ycenter, rows or height
    for (int yctr = 0; yctr < height; yctr++)
    {
        // For loop to set the value of xcenter, columns or width
        for (int xctr = 0; xctr < width; xctr++)
        {

	        	int counter = 0;
	        	int sumRed = 0;
	        	int sumGreen = 0;
	        	int sumBlue = 0;

            // For loop to set the value of yoffset, to get surrounding pixels
            for (int yoff = -1; yoff < 2; yoff++)
            {

	                int ycur = yctr + yoff;
	                if (ycur < 0)
	                    continue;
	                if (ycur >= height)
	                    continue;

                for (int xoff = -1; xoff < 2; xoff++)
                {
                    	int xcur = xctr + xoff;
                    	if (xcur < 0)
                        	continue;
		                if (xcur >= width)
        	                continue;

                // Adds the value of verified pixel to the sum
                    tmp = &image[ycur][xcur];
                    sumRed += tmp->rgbtRed;
                    sumGreen += tmp->rgbtGreen;
                    sumBlue += tmp->rgbtBlue;
                    counter++;      // To count the occurences, to calculate average later
                }
            }

            // Sets new color based on average of surrounding pixels
            tmp = &temp[yctr][xctr];

            sumRed = round((double) sumRed / counter);
            tmp->rgbtRed = (sumRed < 255) ? sumRed : 255;

            sumGreen = round((double) sumGreen / counter);
            tmp->rgbtGreen = (sumGreen < 255) ? sumGreen : 255;

            sumBlue = round((double) sumBlue / counter);
            tmp->rgbtBlue = (sumBlue < 255) ? sumBlue : 255;
        }
    }

#if 1
    tmp = &temp[0][0];
    img = &image[0][0];

    int idxlim = width * height;
    for (int idxcur = 0; idxcur < idxlim; idxcur++)
        img[idxcur] = tmp[idxcur];
#endif
}

int max(int s)
{
    if (s > 255)
    {
        s = 255;
        return 1;
    }
    else
    {
        return 0;
    }
}