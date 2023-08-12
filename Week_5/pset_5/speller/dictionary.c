// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Initialize variable for counting words
unsigned int count = 0;

// Initialize variable for hash
unsigned int hash_value;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hash_value = hash(word);

    // Initialize a variable to serve as cursor
    node *cursor = table[hash_value];

    // iterate  through the list
    while (cursor != 0)
    {
        // Make a crosscheck
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        // If not found move the cursor on the indexed list
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Grab the file to check
    FILE *input_file = fopen(dictionary, "rb");
    if (input_file == NULL)
    {
        return false;
    }

    // Iterate through the each character from the input file
    char c[LENGTH + 1];
    while (fscanf(input_file, "%s", c) != EOF)
    {
        // Allocate memory
        node *tmp = malloc(sizeof(node));

        // Base case
        if (tmp == NULL)
        {
            return false;
        }

        // Copy the word
        strcpy(tmp->word, c);
        tmp->next = NULL;

        int index = hash(c);
        if (table[index] == NULL)
        {
            table[index] = tmp;
        }
        else
        {
            tmp->next = table[index];
            table[index] = tmp;
        }

        count++;
    }

    // Close the open file
    fclose(input_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (count > 0)
    {
        return count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
