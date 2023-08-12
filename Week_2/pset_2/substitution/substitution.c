#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check if the command-line arguments were provided correctly
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Innitialize variables
    string key = argv[1];
    int key_length = strlen(key);

    // Validate the key
    // Check for key length of 26 characters
    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int key_check_unique[26] = {0};

    for (int i = 0; i < key_length; i++)
    {
        // Check for non-alphabetic characters
        if (!isalpha(key[i])) // ! is used to check for the opposite (not alphanumeric)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        // Check for repeated characters (case insensitive using tolower())
        int index = tolower(key[i]) - 'a';

        if (key_check_unique[index])
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }

        // Mark the encountered characters to keep track of any possible duplicates
        key_check_unique[index] = 1;
    }

    // Get plaintext with get_string
    string plaintext = get_string("plaintext: ");

    int plaintext_length = strlen(plaintext);
    string ciphertext = plaintext;

    // Encipher
    for (int i = 0; i < plaintext_length; i++)
    {
        // Leave non alphabetic characters as is
        if isalpha(plaintext[i])
        {
            // For each letter of the plaintext, map it to the cipher provided in the key
            char shift = isupper(plaintext[i]) ? 'A' : 'a';

            // Preserve case
            int key_index = tolower(plaintext[i]) - 'a';
            ciphertext[i] = isupper(plaintext[i]) ? toupper(key[key_index]) : tolower(key[key_index]);
        }
    }

    // Print the ciphertext
    printf("ciphertext: %s\n", ciphertext);
}