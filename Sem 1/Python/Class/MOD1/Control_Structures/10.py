# Question: Write a program to find the sum of first n even numbers.
# Module: MOD1
# Section: Control_Structures

# MOD1 - Control_Structures: Question 10
# Write your Python program here.

# Example skeleton:
# print('Hello')



n = int(input("Enter a number: "))

sum = 0

for i in range(1, n + 1):
    if i % 2 == 0:
        sum = sum + i

print(sum)

