// Prints Hello, world
// by Wojciech Szubstarski 2018 for CS50.

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get input from user
    string name = get_string("What is your name?\n");

    // Prints hello with user input
    printf("hello, %s\n", name);
}