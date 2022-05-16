# Identifies a person based on their DNA sample and STRs like FBI do.
# by Wojciech Szubstarski 2021 for CS50.

from csv import DictReader
from csv import reader
from sys import argv
from sys import exit

# Ensure proper usage
if len(argv) != 3:
    print("Usage: python dna.py DATABASE_file.csv SEQUENCE_file.txt")
    exit(1)

# Open the CSV file and read STRs into memory
with open(argv[1], "r") as suspects_file:
    suspects = reader(suspects_file)

    for row in suspects:
        STRs = row
        STRs.pop(0)
        break

# open the CSV file and read suspects without header into memory
with open(argv[1], "r") as suspects_file:
    suspects = list(DictReader(suspects_file))

# Open the DNA sequence and read its contents into memory
with open(argv[2], "r") as DNA_file:
    sample = DNA_file.read()
    sample = sample.rstrip("\n")

# Convert extracted STRs to STRs dictionary
subseq = {}
for STR in STRs:
    subseq[STR] = 1

# Compute the longest run of consecutive repeats of the STR in the DNA sequence to identify
for key in subseq:
    l = len(key)
    highestValue = 0
    value = 0
    for i in range(len(sample)):

        # Resets repetitions value to next STR run
        value = 0

        # Compare if the part of the sample match the key and repeating itself and start counting repetitions.
        if sample[i: i + l] == key:

            while sample[i - l: i] == sample[i: i + l]:
                value += 1
                i += l

            # Compare quantity of repetitions to the highest value. If current is the highest, replaces it.
            if value > highestValue:
                highestValue = value

    # Save the longest run in the dictionary.
    subseq[key] += highestValue

for person in suspects:
    match = 0

    # Checks if any person STRs matches STRs in STRs in sample
    for sample in subseq:
        if subseq[sample] == int(person[sample]):
            match += 1

    # If any person STRs matches STRs in STRs in sample, prints name of that person
    if match == len(subseq):
        print(person['name'])
        exit(0)

# If not... prints "No match"
print("No match")
exit(0)