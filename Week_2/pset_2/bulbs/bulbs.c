#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    // Get user input message
    string text = get_string("Message: ");

    //  Loop through each character of the input message
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];

        // Convert each single char into binary of 8 bits
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            // Shift characters to the right by 7 - j positions
            int shifted_char = c >> (BITS_IN_BYTE - 1 - j);

            // Get the least significant bit using the modulo operator
            int bit = shifted_char % 2;

            //  Print the corresponding bulb color for the character
            print_bulb(bit);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
