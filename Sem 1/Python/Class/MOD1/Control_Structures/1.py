# Question: Write a program to check whether a number is divisible by both 3 and 5.
# Module: MOD1
# Section: Control_Structures

# MOD1 - Control_Structures: Question 1
# Write your Python program here.

# Example skeleton:
# print('Hello')


val = int(input("Enter a number: "))

if (val % 3 == 0) and (val % 5 == 0):
    print(val, "is divisible by 3 and 5")
else:
    print(val, "is not divisible by 3 and 5")
