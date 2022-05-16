// Builds a pyramid of user chioce height
// by Wojciech Szubstarski 2018 for CS50.

#include <stdio.h>
#include <cs50.h>

int height;

int main(void)
{
    //Prompt user for a number and make a validation.
    do
    {
        height = get_int("Let's build a piramid! Enter height between 1 and 8: ");
    }
    while (height < 1 || height > 8);

    //Build a pyramid tier by tier.
    for (short h = 0; h < height; h++)
    {
        //Prints blank spaces.
        for (short i = height - h - 1; i > 0; i--)
        {
            printf(" ");
        }
        //Prints first half of pyramid.
        for (short j = 0 ; j < h + 1; j++)
        {
            printf("#");
        }
        //Prints the gap.
        printf("  ");
        //Pints second half of pyramid.
        for (short j = 0 ; j < h + 1; j++)
        {
            printf("#");
        }
        //Make next tier.
        printf("\n");
    }
}