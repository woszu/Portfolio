// Encrypts messages using Vigeneres’s cipher by the key given in executing parameter.
// by Wojciech Szubstarski 2018 for CS50.
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>



int main(int argc, string argv[])
{
    //checks if number of parameters is correct.
    if (argc != 2)
    {
        printf("Too many or not enough parameters. Execute program only with one parameter.\n");
        return 1;
    }
    // Checks if every char in argument is alphanumeric.
    for (int i = 0, j = strlen(argv[1]); i < j; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Parameter must be alphanumeric!\n");
            return 1;
        }
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    // Encoding a message.
    for (int i = 0, j = strlen(text), k = 0; i < j; i++)
    {
        if (isalpha(text[i]) && isupper(text[i]) && isupper(argv[1][k]))
        {
            char cipher = ((text[i] + (char) argv[1][k] - 65 - 65) % 26) + 65;
            printf("%c", cipher);
            k++;
        }
        else if (isalpha(text[i]) && isupper(text[i]) && islower(argv[1][k]))
        {
            char cipher = ((text[i] + (char) argv[1][k] - 65 - 97) % 26) + 65;
            printf("%c", cipher);
            k++;
        }
        else if (isalpha(text[i]) && islower(text[i]) && islower(argv[1][k]))
        {
            char cipher = ((text[i] + (char) argv[1][k] - 97 - 97) % 26) + 97;
            printf("%c", cipher);
            k++;
        }
        else if (isalpha(text[i]) && islower(text[i]) && isupper(argv[1][k]))
        {
            char cipher = ((text[i] + (char) argv[1][k] - 97 - 65) % 26) + 97;
            printf("%c", cipher);
            k++;
        }
        //Other output is not encoded.
        else
        {
            printf("%c", text[i]);
        }
        // resets key, when all letters used
        if (k == strlen(argv[1]))
        {
            k = 0;
        }
    }
    printf("\n");
    return 0;
}