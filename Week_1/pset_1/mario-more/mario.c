#include <stdio.h>
#include <cs50.h>

int get_size(void);
void print_grid(int size);

int main(void)
{
    // Get size of grid
    const int n = get_size();

    // Print grid of bricks
    print_grid(n);

}

int get_size(void)
{
    // Prompt the size of the grid
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void print_grid(int size)
{
    for (int i = 1; i <= size; i ++)
    {
        // Print spaces on the left side of the pyramid
        for (int j = 0; j < size - i; j ++)
        {
            printf(" ");
        }

        // Print the Hash "#" on the left side
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Print the middle spaces of the pyramid
        printf("  ");

        // Print the hash on the right side
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // // Print spaces on the right side of the pyramid
        // for (int j = 0; j < size - i; j ++)
        // {
        //     printf(" ");
        // }

        // Print a new line
        printf("\n");
    }
}