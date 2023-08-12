#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get credit card number from the user
    long long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number <= 0);

    // Calculate checksum according to Luhn's algorithm
    int sum = 0;
    int digit_count = 0;
    long long num = card_number;

    while (num > 0)
    {
        int digit = num % 10;
        num /= 10;
        digit_count++;

        if (digit_count % 2 == 0)
        {
            digit *= 2;
            sum += (digit % 10) + (digit / 10);
        }
        else
        {
            sum += digit;
        }
    }

    // Check if the checksum is valid and determine the card type
    if (sum % 10 == 0)
    {
        // Determine card type based on the first digit(s)
        int first_two_digits = card_number / 10000000000000LL; // 15-digit American Express cards
        int first_two_digits_2 = card_number / 100000000000000LL; // 16-digit Mastercard cards
        int first_digit = card_number / 1000000000000000L; // 16-digit Visa cards
        int first_digit_2 = card_number / 1000000000000L; // For 13-digit Visa cards

        if ((digit_count == 15) && (first_two_digits == 34 || first_two_digits == 37))
        {
            printf("AMEX\n");
        }
        else if (((digit_count == 16) && (first_digit == 4)) || ((digit_count == 13) && (first_digit_2 == 4)))
        {
            printf("VISA\n");
        }
        else if ((digit_count == 16) && (first_two_digits_2 >= 51 && first_two_digits_2 <= 55))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
