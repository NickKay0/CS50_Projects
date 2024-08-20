// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1126; // 26;

// Hash table
node *table[N];

// total words loaded
int total_words = 0;

// search reccursively nodes at hash index for word
bool find_word(const char *word, node *n)
{
    if (n == NULL)
    {
        return false;
    }

    if (strcmp(n->word, word) == 0)
    {
        return true;
    }
    else
    {
        return find_word(word, n->next);
    }
}

// Capitalizes a string
void capitalize_string(char *word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]))
        {
            word[i] = toupper(word[i]);
        }
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

    char *wordUpper = malloc(strlen(word) + 1);
    strcpy(wordUpper, word);
    capitalize_string(wordUpper);

    bool ret = find_word(wordUpper, table[index]);
    free(wordUpper);
    return ret;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    // Return the sum of ASCII values
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += toupper(word[i]) - 'A';
    }

    return sum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // open the dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // read for each word of the dictionary
    char line[LENGTH + 2];
    while (fgets(line, sizeof(line), dict))
    {
        // hash the word
        char *token = strtok(line, "\n");
        capitalize_string(token);
        int index = hash(token);

        // create node with the word
        node *n = malloc(sizeof(node));
        strcpy(n->word, token);

        // insert into hash table
        if (table[index] == NULL)
        {
            // n->next = table[index]->next;
            n->next = NULL;
            table[index] = n;
        }
        else
        {
            n->next = table[index]->next;
            table[index]->next = n;
        }

        // add to total words
        total_words++;
    }

    // close the dictionary file
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return total_words;
}

// Frees nodes from the table
void free_nodes(node *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->next != NULL)
    {
        return free_nodes(node->next);
    }
    else
    {
        free(node);
        return;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            free_nodes(table[i]);
        }
    }

    return true;
}
