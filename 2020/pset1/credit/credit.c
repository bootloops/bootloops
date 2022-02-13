#include <stdio.h>
#include <cs50.h>
#include <math.h> //this is required to perform the math i need

// this is for the credit card fraud detection
// through calculation deduction
/*
the way this is supposed to work is
    1, input valid CC number
        while :
        1a, not positive integer, prompt for re-entry
        1b, must be >13 and <17 digits
    2, Checksum calculation
        2a,do checksum that card number, while final digit != 0, print "Enter valid card number: "

        2b,check which card is it?
            -if 15-16 digits, check first_two digits for AMEX,or MC
            -if 13 or 16 digits, check for first digit 4 == visa
    3, Output
        3a Display identified card if matching valid definitions, or
        3b Dispaly INVALID
    test you program on valid/invalid numbers
*/
void number_checker(void); //digit checker function
void card_checker(long n); //card loop definition
void AMEX(long n); //AMEX definition
void VISA(long n); //VISA definition
void MC(long n); //MC deifinition
int checkSum = 0;

int main(void)
{
    //intro
    printf("Let see what credit card you got!\n\t");
    number_checker();
    printf("");
}

void MC(long n)
{
    /* FIRST ATTEMPT using AMEX
    long double base, exp, amex_card37, amex_card34;

    LENGTH = 15 digits
    //FIRST_TWO_DIGITS = 34 or 37
    base37 = (3.7); // 370,000,000,000,000
    base34 = (3.4); // 340,000,000,000,000
    exp = (13);
    amex_card37 = pow(base37, exp);
    amex_card34 = pow(base34, exp);

    printf("AMEX,\n %Lf", max_value);
    */

    /* SECOND ATTEMPT changed to MC */
    long double card_number, exp, result;
    /*
    Master Card
 5,203,600,000,000,014
 	-5203600000000014 mod 10 = 4
	-5203600000000014 mod 100 = 14
	-5203600000000014 mod 1,000,000,000,000 = 600,000,000,014
	-5203600000000014 mod 10,000,000,000,000 = 3.6*10^12
	-5203600000000014 mod 100,000,000,000,000 = 3.6*10^12
	-5203600000000014 mod 1,000,000,000,000,000 = 2.036*10^14
	-5203600000000014 mod 10,000,000,000,000,000[17,0's] = [ 5.2036*10^15 ]

	NOTE-- final part of the check will involve mod 10, to check the very last digit being 0
	*/
	exp = 10000000000000000
    result = card_number % exp
}
/*
void MC(long n)
{

    //LENGTH = 16 digits
    //FIRST_TWO_DIGITS = 51 or 52 or 53 or 54 or 55
    long double max_value = (5.5 * 10^14); // 5,500,000,000,000,000
    long double min_value = (5.1 * 10^14); // 5,100,000,000,000,000
    printf("MASTERCARD,\n %l", max_value);
}

void VISA(long n)
{
    //LENGTH = 13 or 16 digits
    //FIRST_DIGIT = 4
    long double max_value = (4 * 10^16); // 4,000,000,000,000,000
    long double min_value = (4 * 10^13); // 4,000,000,000,000
        if (n == max_value)
        {
        printf("VISA,\n %l", max_value);
        }
}
*/
void number_checker(void)
{
    /*
    STARTING NUMBERS TO CHECK
    AMEX == 34,37;
    MasterCard == 51, 52, 53, 54, 55;
    Visa == 4;

    American Express    MasterCard        Visa;
    15-digit             16-digit     13&16-digit;

    **decimal numbers (0 through 9);
    American Express could print as many as 10^15 = 1,000,000,000,000,000 unique cards! (That’s, um, a quadrillion.)

    must use get_long();
    */

    int cc;

    do {
    cc = get_long("\nEnter CC Number: ");
    }
    while (cc <= 0 || cc > 16);

    // If the digit length is 0> and is >17
    if (cc > 0 && cc < 17)
    {
        printf("--> Your Card Type <--\n");
    }
}
