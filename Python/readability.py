# Computes and print the approximate grade level needed to comprehend some text.
# by Wojciech Szubstarski 2020 for CS50.
from cs50 import get_string

# Asks user for input.
text = get_string("Text: ")

sentences = 0
words = 0
alphachars = 0

# Counts aplha characters, words and sentences in text
for i in range(len(text)):
    if text[i].isalpha():
        alphachars += 1
    if (i == 0 and text[i] != " ") or (i != len(text) - 1 and text[i] == " " and text[i + 1] != " "):
        words += 1
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

# Calculates readability index with Coleman-Liau formula
index = round((0.0588 * (alphachars / words * 100)) - (0.296 * (sentences / words * 100)) - 15.8)

# Prints approximate grade level needed to comprehend input text.
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print("Grade ", + index)