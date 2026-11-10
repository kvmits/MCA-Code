# Question: Write a program to calculate the sum of numbers from 1 to N while skipping multiples of 5.
# Module: MOD1
# Section: Control_Structures

# MOD1 - Control_Structures: Question 12
# Write your Python program here.

# Example skeleton:
# print('Hello')


n = int(input("Enter a number: "))

sum = 0

for i in range(1, n + 1):
    if i % 5 == 0:
        continue
    sum = sum + i

print("Sum =", sum)