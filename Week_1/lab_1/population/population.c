#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_prompt;
    do
    {
        start_prompt = get_int("Start size: ");
    }
    while (start_prompt < 9);

    // TODO: Prompt for end size
    int end_prompt;
    do
    {
        end_prompt = get_int("End size: ");
    }
    while (end_prompt < start_prompt);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (start_prompt < end_prompt)
    {
        start_prompt = start_prompt + (start_prompt / 3) - (start_prompt /4);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}
