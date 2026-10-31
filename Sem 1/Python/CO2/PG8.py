# 8. Write a Python program to find the greatest common divisor (GCD) of two integers using
# recursion.

def gcd(first, second):
    if second == 0:
        return abs(first)
    return gcd(second, first % second)


first = int(input("Enter the first integer: "))
second = int(input("Enter the second integer: "))
print("GCD:", gcd(first, second))

''' Output:

Enter the first integer: 48
Enter the second integer: 18
GCD: 6
'''
