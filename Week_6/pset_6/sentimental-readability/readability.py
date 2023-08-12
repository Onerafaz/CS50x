from cs50 import get_string


def main():
    text = get_string("Text: ")
    L = (count_letters(text) * 100) / count_words(text)
    S = (count_sentences(text) * 100) / count_words(text)
    grade = round(0.0588 * L - 0.296 * S - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    return sum(1 for char in text if char.isalpha())


def count_words(text):
    return len(text.split())


def count_sentences(text):
    return sum(1 for char in text if char in ['.', '!', '?'])


if __name__ == "__main__":
    main()
