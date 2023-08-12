#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Request user input of text
    string text = get_string("Text: ");

    // Calculate the Coleman-Liau index
    float L = (float)count_letters(text) * 100 / count_words(text);
    float S = (float)count_sentences(text) * 100 / count_words(text);
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

    // printf("Index: %i\n", index);
    // printf("Letters: %i\n", count_letters(text));
    // printf("Words: %i\n", count_words(text));
    // printf("Sentences: %i\n", count_sentences(text));
}

int count_letters(string text)
// Counts the number of letters in a word
{
    int count_letters = 0;
    // Loops each word and counts the number of letters
    for (int i = 0; i < strlen(text); i++)
    {
        // Checks if it's an alphanumeric character before adding it to the count
        if (isalpha(text[i]))
        {
            count_letters++;
        }
    }
    return count_letters;
}

int count_words(string text)
// Counts the number of words in a text
{
    int count_words = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // Checks for the number of spaces in a phrase and adds 1 to the end to count the words (might need redoing)
        if (isspace(text[i]))
        {
            count_words++;
        }
    }
    return count_words + 1;
}

int count_sentences(string text)
{
    int count_sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count_sentences++;
        }
    }
    return count_sentences;
}