# Question: Write a program to display numbers in the following pattern:
1
12
123
1234
12345
# Module: MOD1
# Section: Control_Structures

# MOD1 - Control_Structures: Question 8
# Write your Python program here.

# Example skeleton:
# print('Hello')


for i in range(1, 6):
    for j in range(1, i + 1):
        print(j, end="")
    print() #Next line without spacing