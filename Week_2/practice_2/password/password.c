// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool has_lower = false;
    bool has_upper = false;
    bool has_digit = false;
    bool has_symbol = false;

    for (int i = 0; i < strlen(password); i++)
    {
        char c = password[i];

        if (islower(c))
        {
            has_lower = true;
        }
        else if (isupper(c))
        {
            has_upper = true;
        }
        else if (isdigit(c))
        {
            has_digit = true;
        }
        else if (ispunct(c))
        {
            has_symbol = true;
        }

        if (has_lower && has_upper && has_digit && has_symbol)
        {
            return true;
        }
    }

    return false;
}
