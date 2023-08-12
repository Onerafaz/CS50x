#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    // Base case: If the input is just a single digit character, return its integer value
    if (strlen(input) == 1)
    {
        return input[0] - '0';
    }

    // Convert the last character to its numeric value
    int lastDigit = input[strlen(input) - 1] - '0';

    // Shorten the string by removing the last character (moving the null terminator one position to the left)
    input[strlen(input) - 1] = '\0';

    // Recursive step: Return the value of the shortened string plus 10 times the integer value of the last digit
    return convert(input) * 10 + lastDigit;
}