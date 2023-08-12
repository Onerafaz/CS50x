#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check for any non digit in argv[1]
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Prompt for the user input text
    string plaintext = get_string("plaintext: ");

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Encrypt the Plain text
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
}

bool only_digits(string s)
{
    // Make sure every character in s is a digit
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}

char rotate(char c, int n)
{
    // Rotate the character if it's a letter
    if (isupper(c))
    {
        return 'A' + (c - 'A' + n) % 26;
    }
    else if (islower(c))
    {
        return 'a' + (c - 'a' + n) % 26;
    }
    else
    {
        return c;
    }
}