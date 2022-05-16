# Prints minimum number of coins needed to give a change.
# by Wojciech Szubstarski 2018 for CS50.

from cs50 import get_float

while True:
    cash = get_float("Change owed: ")
    if cash >= 0:
        break

cash *= 100
penny = 1
nickel = 5
dime = 10
quarter = 25
coins = 0

# Calculating the result.
while (cash >= quarter):
    cash = cash - quarter
    coins += 1

while (cash >= dime):
    cash = cash - dime
    coins += 1

while (cash >= nickel):
    cash = cash - nickel
    coins += 1

while (cash >= penny):
    cash = cash - penny
    coins += 1

# Shows number of coins.
print(coins)
