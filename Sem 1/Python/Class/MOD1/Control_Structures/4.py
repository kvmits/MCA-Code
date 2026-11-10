# Question: Write a program to find the largest and smallest of three numbers.
# Module: MOD1
# Section: Control_Structures

# MOD1 - Control_Structures: Question 4
# Write your Python program here.

# Example skeleton:
# print('Hello')


n1 = int(input("Num1: "))
n2 = int(input("Num2: "))
n3 = int(input("Num3: "))

if (n1 > n2) and (n1 > n3):
    print(n1, "is the largest")
elif (n2 > n1) and (n2 > n3):
    print(n2, "is the largest")
else: 
    print(n3, "is the largest")
