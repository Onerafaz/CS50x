#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("Whats x? ");
    int y = get_int("Whats y? ");

    if (x < y)
    {
        printf("x is less than y\n");
    }
}
