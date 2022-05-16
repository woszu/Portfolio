// Encrypts messages using Caesar’s cipher by the number given in exetuting parameter.
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
    else
    {
        // Convert string to int.
        int key = atoi(argv[1]);
        string text = get_string("plaintext: ");
        printf("ciphertext: ");

        // Encoding a message.
        for (int i = 0, j = strlen(text); i < j; i++)
        {
            // For CAPITAL LETTERS.
            if (isalpha(text[i]) && isupper(text[i]))
            {
                char cipher = ((text[i] - 65 + key) % 26) + 65;
                printf("%c", cipher);
            }
            // For small letters.
            else if (isalpha(text[i]) && islower(text[i]))
            {
                char cipher = ((text[i] - 97 + key) % 26) + 97;
                printf("%c", cipher);
            }
            //Other output is not encoded.
            else
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");
        return 0;
    }
}