#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompts the user for the Name
    string name = get_string("What's your name? ");
    // Prints the name with the predefined string prefix
    printf("hello, %s\n", name);
}