// Cracks up-to-five digits passwords hashed witch C's DES-based crypt function.
// by Wojciech Szubstarski 2018 for CS50.
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, string argv[])
{
    //checks if number of parameters is correct.
    if (argc != 2)
    {
        printf("Too many or not enough parameters. Execute program only with one parameter.\n");
        return 1;
    }

    // Array of every possible characters allowed in the password sorted by frequency of letters in English language.
    char alpha[54] = {"\0etaoinshrdlcumwfgypbvkjxqzETAOINSHRLDLCUMWFGYPBVKJXQZ"};
    // Extracts "salt".
    char salt[3];
    salt[0] = argv[1][0];
    salt[1] = argv[1][1];
    // Extracts hash.
    char hash[strlen(argv[1]) - 1];

    for (int i = 2, j = strlen(argv[1]), k = 0; i < j; i++, k++)
    {
        hash[i - 2] = argv[1][i];
    }

    //Checks every possible combitation of characters and compares it to given one by the user in the parameter.
    char password[6] = {""};

    for (int f = 0; f < 53; f++)
    {
        for (int e = 0; e < 53; e++)
        {
            for (int d = 0; d < 53; d++)
            {
                for (int c = 0; c < 53; c++)
                {
                    for (int b = 0; b < 53; b++)
                    {
                        for (int a = 0; a < 53; a++)
                        {
                            password[0] = alpha[a];
                            password[1] = alpha[b];
                            password[2] = alpha[c];
                            password[3] = alpha[d];
                            password[4] = alpha[e];
                            password[5] = alpha[f];

                            string check = crypt(password, salt);

                            //Compares if the given string and one of the combinations are the same. If true - print decrypted password.
                            if (strcmp(check, argv[1]) == 0)
                            {
                                printf("%s\n", password);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    // Print if any combination doesn't meet the condition.
    printf("Unable to crack!\n");
    return 2;
}