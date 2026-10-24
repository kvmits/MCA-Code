# 5. Write a Python program to get the factorial of a number using function.

def factorial(number):
    if number < 0:
        raise ValueError("Factorial is not defined for negative numbers.")
    result = 1
    for value in range(2, number + 1):
        result *= value
    return result


num = int(input("Enter a non-negative integer: "))
print("Factorial:", factorial(num))

''' Output:

Enter a non-negative integer: 5
Factorial: 120
'''
