import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    # Initialize empty variable
    db_strs = []

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for person in reader:
            for str_name in reader.fieldnames[1:]:
                person[str_name] = int(person[str_name])
            db_strs.append(person)

    # TODO: Read DNA sequence file into a variable
    # Initialize empty variable
    input_strs = []

    # Loop through chars in input STR's
    with open(sys.argv[2]) as f:
        for line in f:
            input_strs.append(line.strip())

    # TODO: Find longest match of each STR in DNA sequence
    longest_str_matches = {}
    for str_name in db_strs[0].keys():
        if str_name != 'name':
            longest_run = longest_match(input_strs[0], str_name)
            longest_str_matches[str_name] = longest_run

    # TODO: Check database for matching profiles
    for person in db_strs:
        matches = all(
            longest_str_matches[str_name] == person[str_name]
            for str_name in person
            if str_name != 'name'
        )
        if matches:
            print(f"{person['name']}")
            return
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
