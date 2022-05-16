// Determines whether a provided credit card number is valid according to Luhn’s algorithm.
// by Wojciech Szubstarski 2018 for CS50.
#include <cs50.h>
#include <stdio.h>

long long cc_number;

int main(void)
{
    //Prompts user to enter a credit card number and check if is non-negative number.
    do
    {
        cc_number = get_long_long("Enter a credit card number: ");
    }
    while (cc_number < 0);

    // Sum squared numbers.
    int sumdigits = 0;
    long long sqcc_number = cc_number / 10;
    while (sqcc_number > 0)
    {
        int sqdigit = (sqcc_number % 10) * 2;
        if (sqdigit > 9)
        {
            sqdigit = (sqdigit % 10) + 1;
        }
        sumdigits = sumdigits + sqdigit;
        sqcc_number /= 100;
    }
    // Sum squared numbers with other numbers.
    long long otcc_number = cc_number;
    while (otcc_number > 0)
    {
        int otdigit = (otcc_number % 10);
        sumdigits = sumdigits + otdigit;
        otcc_number /= 100;
    }
    // Save first two numbers of credit card and digits of credit card.
    int first_two_numbers, cc_lenght;

    for (cc_lenght = 0; cc_number > 0; cc_lenght++)
    {
        if (cc_number <= 99 && cc_number >= 10)
        {
            first_two_numbers = cc_number;
        }
        cc_number /= 10;
    }
    // Checks if checksum is 0 and prints name of card operator when meets the conditions.
    if (sumdigits % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (first_two_numbers >= 40 && first_two_numbers <= 49 && (cc_lenght == 13 || cc_lenght == 16))
    {
        printf("VISA\n");
    }
    else if (first_two_numbers >= 51 && first_two_numbers <= 55 && cc_lenght == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((first_two_numbers == 34 || first_two_numbers == 37) && cc_lenght == 15)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}