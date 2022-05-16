# Determines whether a provided credit card number is valid according to Luhn’s algorithm.
# by Wojciech Szubstarski 2020 for CS50.
from cs50 import get_int

# Prompts user to enter a credit card number and check if is non-negative number.
while True:
    cc_number = get_int("Number: ")
    if (cc_number > 0):
        break

# Sum squared numbers.
sumdigits = 0
sqcc_number = (cc_number // 10)

while (sqcc_number > 0):
    sqdigit = (sqcc_number % 10) * 2
    if (sqdigit > 9):
        sqdigit = (sqdigit % 10) + 1
    sumdigits = sumdigits + sqdigit
    sqcc_number //= 100

# Sum squared numbers with other numbers.
otcc_number = cc_number

while (otcc_number > 0):
    otdigit = (otcc_number % 10)
    sumdigits = sumdigits + otdigit
    otcc_number //= 100

# Save first two numbers of credit card and digits of credit card.
cc_lenght = 0

while (cc_number > 0):
    if (cc_number <= 99 and cc_number >= 10):
        first_two_numbers = cc_number
        cc_lenght += 2
        break
    else:
        cc_number //= 10
        cc_lenght += 1

# Checks if checksum is 0 and prints name of card operator when meets the conditions.
if (sumdigits % 10 != 0):
    print("INVALID")

elif (first_two_numbers >= 40 and first_two_numbers <= 49 and (cc_lenght == 13 or cc_lenght == 16)):
    print("VISA")

elif (first_two_numbers >= 51 and first_two_numbers <= 55 and cc_lenght == 16):
    print("MASTERCARD")

elif ((first_two_numbers == 34 or first_two_numbers == 37) and cc_lenght == 15):
    print("AMEX")

else:
    print("INVALID\n")