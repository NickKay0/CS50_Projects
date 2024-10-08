import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Incorrect number of arguments.")
        return

    # TODO: Read database file into a variable
    db = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            db.append(row)

    # TODO: Read DNA sequence file into a variable
    sequence = ""
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    # Get the subsequences to search for
    subsequences = []
    for key in db[0]:
        if key.lower() != "name":
            subsequences.append(key)
    subsequences = {key: 0 for key in subsequences}

    for key in subsequences:
        subsequences[key] = longest_match(sequence, key)

    # TODO: Check database for matching profiles
    name = "No match"
    for row in db:
        for key in subsequences:
            if int(row[key]) != int(subsequences[key]):
                break

            if key == list(subsequences.keys())[-1]:
                name = row["name"]

    print(name)
    return


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
