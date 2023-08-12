from cs50 import get_int
import re


def main():
    # Get credit card number from the user
    card_number = get_int("Number: ")

    # Calculate checksum according to Luhn's algorithm
    sum = 0
    digit_count = 0
    num = card_number

    while num > 0:
        digit = num % 10
        num //= 10
        digit_count += 1

        if digit_count % 2 == 0:
            digit *= 2
            sum += digit % 10 + digit // 10
        else:
            sum += digit

    # Validate the input from user
    if check(card_number):
        # Check if the checksum is valid and determine the card type
        if sum % 10 == 0:
            # Determine card type based on the first digit(s)
            first_two_digits = card_number // 10**13  # 15-digit American Express cards
            first_two_digits_2 = card_number // 10**14  # 16-digit Mastercard cards
            first_digit = card_number // 10**15  # 16-digit Visa cards
            first_digit_2 = card_number // 10**12  # For 13-digit Visa cards

            if (digit_count == 15) and (first_two_digits == 34 or first_two_digits == 37):
                print("AMEX")
            elif ((digit_count == 16) and (first_digit == 4)) or (
                (digit_count == 13) and (first_digit_2 == 4)
            ):
                print("VISA")
            elif (digit_count == 16) and (51 <= first_two_digits_2 <= 55):
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")


def check(card_number):
    # Check for digits from 0-9
    if not re.match(r"^\d+$", str(card_number)):
        return False

    # Check the length of the card
    if len(str(card_number)) not in [13, 15, 16]:
        return False

    return True


if __name__ == "__main__":
    main()
