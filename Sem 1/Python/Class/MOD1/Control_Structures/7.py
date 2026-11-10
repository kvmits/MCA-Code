# Question: Write a program to find the factorial of a number using a for loop.
# Module: MOD1
# Section: Control_Structures

# MOD1 - Control_Structures: Question 7
# Write your Python program here.

# Example skeleton:
# print('Hello')

num = int(input("Enter a number: "))

fact = 1

for i in range(1,num + 1):
    fact = fact * i

print("Factorial =", fact)