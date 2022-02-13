#include <stdio.h>
#include <cs50.h>
#include <math.h>

void input_change_for(void);
void cal_change(void);
void output_stuff(void);
float change;
double penny = 0.01, nickel = 0.05, dime = 0.10, quarter = 0.25;
double coins[4] = {0.01, 0.05, 0.10, 0.25};
int if_check[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, a;
int r_change, c_change;
int qcount = 0, pcount = 0, ncount = 0, dcount = 0;

/*
    eg.
    9.75 x 100 = 975
    975 % 100 = 75 (cents left) == remainder-var
        if (remainder-var < 100 && remainder-var > 25); then remainder - 0.25*100 = new_remainder[50]. if (new_remainder > 25 && < 100); then new_remainder - 0.25*100 = new_remainder[25];again -- rince repeat.
        if (remainder-var < 25 && remainder-var > 10); then remainder - 0.10*100 = new_remainder. -- rince repeat
        if (remainder-var < 10 && remainder-var > 5); then remainder - 0.05*100 = new_remainder. -- rince repeat
        if (remainder-var < 5 && remainder-var > 0); then remainder - 0.01*100 = new_remainder. -- rince repeat

*/

//EXECUTE
int main(void)
{
    input_change_for();
    cal_change();
    output_stuff();

}


//FUNCTIONS
void input_change_for(void)
{

do
{
    change = get_float("Change owed: ");

}
while (change <= 0);


}

void output_stuff(void)
{
    //printf("TOTAL: %d \t REMAINDER: %d \n", c_change, r_change);
    //printf("Quarters: %d\n", qcount);
    //printf("Dimes: %d\n", dcount);
    //printf("Nickels: %d\n", ncount);
    //printf("Pennies: %d\n", pcount);
    int total_coins = qcount + dcount + ncount + pcount;
    printf("%d\n", total_coins);
}

void cal_change(void)
{
c_change = round(change * 100);
r_change = c_change % 100;
int csum = c_change; //csum is the total change amount converted to pennies
int sum = r_change; //sum is the remainder of the change mod 100
while (csum >= 25) //quarters
{
    qcount++;
    //printf("QUARTER: %d += %d - %f * 100 = %f \n", csum, csum, quarter, csum - quarter * 100); //use for calc check
    csum = round(csum - quarter * 100); //for the dollar
}
while (csum >= 10 && csum < 25) //dimes
{
    dcount++;
    //printf("QUARTER: %d += %d - %f * 100 = %f \n", csum, csum, quarter, csum - quarter * 100); //use for calc check
    csum = round(csum - dime * 100); //for the dollar
}
while (csum >= 5 && csum < 10) //nickels
{
    ncount++;
    //printf("QUARTER: %d += %d - %f * 100 = %f \n", csum, csum, quarter, csum - quarter * 100); //use for calc check
    csum = round(csum - nickel * 100); //for the dollar
}
while (csum >= 1 && csum < 5) //pennies
{
    pcount++;
    //printf("QUARTER: %d += %d - %f * 100 = %f \n", csum, csum, quarter, csum - quarter * 100); //use for calc check
    csum = csum - penny * 100; //for the dollar
}

}
/* After 4 long days... i think maybe 5, it finally clicked. */