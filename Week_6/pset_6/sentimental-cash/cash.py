from cs50 import get_float


def main():
    cents = get_cents()

    quarters = get_quarters(cents)

    dimes = calculate_dimes(cents)

    nickels = calculate_nickels(cents)

    pennies = calculate_pennies(cents)

    coins = quarters + dimes + nickels + pennies

    return coins


def get_cents():
    while True:
        try:
            dollars = get_float("Change owed: ")
            if dollars > 0:
                cents = round(dollars * 100)
                return cents
            print("Please enter a positive value.")
        except ValueError:
            print("Invalid input. Please enter a number.")


def get_quarters(cents):
    return cents // 25


def calculate_dimes(cents):
    remaining_cents = cents % 25
    return remaining_cents // 10


def calculate_nickels(cents):
    remaining_cents = cents % 25
    remaining_cents %= 10
    return remaining_cents // 5


def calculate_pennies(cents):
    remaining_cents = cents % 25
    remaining_cents %= 10
    remaining_cents %= 5
    return remaining_cents


if __name__ == "__main__":
    result = main()
    print(result)
