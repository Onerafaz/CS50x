#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    // Innitialize the variables to 0
    int total_hours = 0;
    float average_hours = 0;

    // Calculate the total hours
    for (int i = 0; i < weeks; i++)
    {
        total_hours += hours[i];
    }

    // Calculate the average hours
    if (weeks > 0)
    {
        average_hours = (float)total_hours / weeks;
    }

    // Check for the input of the desired result format of 'T' or 'A'
    if (output == 'T')
    {
        return total_hours;
    }
    else
    {
        return (float)average_hours;
    }
}