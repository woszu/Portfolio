// Re-implementation load, hash, check, size, and unload functions so that spell checker works as advertised.
// by Wojciech Szubstarski 2020 for CS50.

// Including stdio.h for input/output functions such as fopen, fscanf, fclose.
#include <stdio.h>
// Including string.h for string functions such as strlen, strcpy, strcmp.
#include <string.h>
// Including ctype.h for function tolower to make hash function working correctly.
#include <ctype.h>
// Including stdlib.h for malloc and free functions.
#include <stdlib.h>

//stdbool.h is declared in dictionary.h.

#include "dictionary.h"

// Create a node structure in the hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table enough to handle dictionaries
const unsigned int N = 30000000;

// Create a hash table made of nodes.
node *hashtable[N];

// Hashes word to a number
// A case-insensitive implementation of the djb2 hash function.
// Adapted by Neel Mehta from
// http://stackoverflow.com/questions/2571683/djb2-hash-function.

unsigned int hash_word(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    hash = hash % N;
    return hash;
}

// Checks if word is in the dictionary.
bool check(const char *word)
{
    char if_in_dict[strlen(word)];

    strcpy(if_in_dict, word);

    // Makes spell-checking case-insensitive
    for (int i = 0; i < strlen(word); i++)
    {
        if_in_dict[i] = tolower(if_in_dict[i]);
    }
    int index = hash_word(if_in_dict);

    if (hashtable[index] == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int word_counter = 0;

// Loads dictionary to memory.

bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        fclose(dict);
        return false;
    }

    // Search, adds words to hashtable with nodes containing words found in dictionary and calculate thair quantity)
    char word[LENGTH + 1];
    node *new_node;


    while (fscanf(dict, "%s", word) != EOF)
    {
        word_counter++;
        do
        {
            // Mallocs memory for new words/nodes.
            new_node = malloc(sizeof(node));

            // Checks if malloc succeeded.
            if (new_node == NULL)
            {
                free(new_node);
            }
        }
        while (new_node == NULL);

        // Makes new nodes for new words
        strcpy(new_node->word, word);

        // Calculates word index and adds it to hashtable.
        int h = hash_word(word);
        new_node->next = hashtable[h];
        hashtable[h] = new_node;
        node *head = hashtable[h];
    }
    fclose(dict);
    return true;
}
// Shows sum of words in dictionary
unsigned int size(void)
{
    return word_counter;
}
// Unloads dictionary in order to free memory.

bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i] != NULL)
        {
            node *cursor = NULL;
            cursor = hashtable[i];
            while (cursor != NULL)
            {
                node *temp = cursor;
                cursor = cursor->next;
                free(temp);
            }
        }
    }
    return true;
}
