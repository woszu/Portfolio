// Prints minimum number of coins needed to give a change.
// by Wojciech Szubstarski 2018 for CS50.
#include <cs50.h>
#include<math.h>
#include <stdio.h>

float cash;
short penny = 1, nickel = 5, dime = 10, quarter = 25;
int coins = 0;

int main(void)
{
    //Prompts user to enter amount in dollars and validate it.
    do
    {
        cash = get_float("How many $ I owe you? ");
    }
    while (cash < 0);
    //Change dollars to pennies.
    cash *= 100;
    cash = round(cash);
    //Calculating the result.
    while (cash >= quarter)
    {
        cash = cash - quarter;
        coins++;
    }
    while (cash >= dime)
    {
        cash = cash - dime;
        coins++;
    }
    while (cash >= nickel)
    {
        cash = cash - nickel;
        coins++;
    }
    while (cash >= penny)
    {
        cash = cash - penny;
        coins++;
    }
    //Shows number of coins.
    printf("%i\n", coins);
}