# 7. Write a Python program to solve the Fibonacci sequence using recursion.

def fibonacci(number):
    if number <= 1:
        return number
    return fibonacci(number - 1) + fibonacci(number - 2)


terms = int(input("Enter the number of Fibonacci terms: "))
if terms < 0:
    raise ValueError("The number of terms cannot be negative.")
print("Fibonacci sequence:", [fibonacci(index) for index in range(terms)])

''' Output:

Enter the number of Fibonacci terms: 8
Fibonacci sequence: [0, 1, 1, 2, 3, 5, 8, 13]
'''
