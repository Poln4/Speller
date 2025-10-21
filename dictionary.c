// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// tracking words while loading the hash table to later size it
unsigned int tracked_word;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to obtain a hash value
    int index = hash(word);
    // accesss linked list with a cursor
    node *cursor = table[index];

    while (cursor != NULL)
    {
        int result;
        result = strcasecmp(cursor->word, word);

        if (result == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Math using all the letter!
    unsigned long total = 0;

    // iterar por cada letra
    for (int i = 0; i < strlen(word); i++)
    {
        int value = toupper(word[i]);
        total += value;
    }
    // return the remainder :L
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Let's open the dictionary
    FILE *infile = fopen(dictionary, "r");
    if (!infile)
    {
        printf("Error opening file!\n");
        return false;
    }

    // Let's look for words!
    char word[LENGTH + 1];
    while (fscanf(infile, "%s", word) != EOF)
    {
        // alocating memory for new words
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            return 1;
        }
        // coping the words from the dictionary into the new node
        strcpy(new_word->word, word);
        // getting the hash value/index
        int index = hash(word);
        // connecting the new word to the linked list
        new_word->next = table[index];
        // linking the hash table to the new linked list
        table[index] = new_word;
        tracked_word++;
    }
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // check the number of words tracked while loading the has table
    if (tracked_word > 0)
    {
        return tracked_word;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Get to each index at the table first
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        // with a cursor, free every linked list;
        while (cursor != NULL)
        {
            node *ptr = cursor->next;
            free(cursor);
            cursor = ptr;
        }
    }
    return true;
}
