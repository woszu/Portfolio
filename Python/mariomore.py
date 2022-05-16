# Builds a pyramid of user chioce height
# by Wojciech Szubstarski 2020 for CS50.

from cs50 import get_int

# Prompt user for a number and make a validation.
while True:
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break

# Prints blank spaces and hashtags
for h in range(height):
    print(" " * (height-h-1) + "#" * (h+1) + "  " + "#" * (h+1))
    h -= 1