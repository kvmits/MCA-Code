#Write a program to find the sum of digits of a number. Display the reverse of the number.

n = 12345
digits = str(n)
sum = sum(int(digit) for digit in digits)
rev = digits[::-1]
print("Sum of digits:", sum)
print("Reverse of the number:", rev)

''' Output:

Sum of digits: 15
Reverse of the number: 54321
'''
