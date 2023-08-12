import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit('Usage: python dna.py data.csv sequence.txt')

    # Read database file into a variable
    database = read_database(sys.argv[1])

    # Read DNA sequence file into a variable
    dna_sequence = read_dna_sequence(sys.argv[2])

    # TODO: Find longest match of each STR in DNA sequence
    longest_str_matches = {}
    for str_name in database[0].keys():
        if str_name != 'name':
            longest_run = find_longest_match(dna_sequence[0], str_name)
            longest_str_matches[str_name] = longest_run

    # Check database for matching profiles
    for person in database:
        if person_matches(longest_str_matches, person):
            print(person['name'])
            return
    print('No match')


def read_database(filename):
    # TODO: Read database file into a variable
    db_strs = []

    with open(filename) as file:
        reader = csv.DictReader(file)
        for person in reader:
            for str_name in reader.fieldnames[1:]:
                person[str_name] = int(person[str_name])
            db_strs.append(person)

    return db_strs


def read_dna_sequence(filename):
    # TODO: Read DNA sequence file into a variable
    input_strs = []

    with open(filename) as f:
        for line in f:
            input_strs.append(line.strip())

    return input_strs


def find_longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0

        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


def person_matches(longest_str_matches, person):
    # TODO: Check database for matching profiles
    for str_name, value in longest_str_matches.items():
        if str_name != 'name' and person[str_name] != value:
            return False
    return True


if __name__ == '__main__':
    main()
