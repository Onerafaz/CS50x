// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string replace(const string word);

int main(int argc, string argv[])
{
    //  Check for the proper number of command line inputs
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    string modified_word = replace(argv[1]);
    printf("%s\n", modified_word);

    free(modified_word);
}

string replace(const string word)
{
    string replaced = (string)malloc(strlen(word) + 1);
    size_t i = 0;

    while (word[i])
    {
        char c = tolower(word[i]);

        switch (c)
        {
            case 'a':
                replaced[i] = '6';
                break;
            case 'e':
                replaced[i] = '3';
                break;
            case 'i':
                replaced[i] = '1';
                break;
            case 'o':
                replaced[i] = '0';
                break;
            default:
                replaced[i] = word[i];
                break;
        }
        i++;
    }

    replaced[i] = '\0'; // Add the null terminator to the end of the replaced string
    return replaced;
}