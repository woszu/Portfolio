// Computes and print the approximate grade level needed to comprehend some text.
// by Wojciech Szubstarski 2021 for CS50.

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float sentences = 0;
float words = 0;
float alphachars = 0;

int main(void)
{

    //Asks user for input.
    string text = get_string("Text: ");

    // Counts alpha characters, words and sentences in text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            alphachars++;
        }
        if (((i == 0) && (text[i] != ' ')) || ((i != (n - 1)) && (text[i] == ' ') && ((text[i + 1]) != ' ')))
        {
            words++;
        }
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            sentences++;
        }
    }


    // Calculates readability index with Coleman-Liau formula
    float L = 100 * alphachars / words;
    float S = 100 * sentences / words;
    int index = 0;
    index = round(0.0588 * L  - 0.296 * S - 15.8);

    // Prints approximate grade level needed to comprehend input text.
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}