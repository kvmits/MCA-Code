# Question: Write a program to find the sum of digits of a number. Display the reverse of the number.
# Module: MOD1
# Section: Control_Structures

# MOD1 - Control_Structures: Question 11
# Write your Python program here.

# Example skeleton:
# print('Hello')


n = int(input("Enter a number: "))

sum = 0
rev = 0

while n > 0:
    digit = n % 10
    sum = sum + digit
    rev = rev * 10 + digit
    n = n // 10

print("Sum =", sum)
print("Reverse =", rev)