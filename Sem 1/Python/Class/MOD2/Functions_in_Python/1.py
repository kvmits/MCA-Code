# Question: Write a Python program to define and call a function to find the largest of three numbers.
# Module: MOD2
# Section: Functions_in_Python

# MOD2 - Functions_in_Python: Question 1
# Write your Python program here.

# Example skeleton:
# print('Hello')


def large(n1, n2, n3):
    largest = n1  
    if n2 > largest:
        largest = n2  
    if n3 > largest:
        largest = n3  
    return largest  
num1 = int(input("Enter the first number: "))
num2 = int(input("Enter the second number: "))
num3 = int(input("Enter the third number: "))
largest_number = large(num1, num2, num3)
print("The largest Number is :", largest_number)



'''
Output:
Enter the first number: 10
Enter the second number: 20
Enter the third number: 30
The largest Number is : 30
'''