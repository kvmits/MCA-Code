#Write a program to swap the values of two variables with and without using temporary variable.

a = 10
b = 20

temp = a
a = b
b = temp
print("After swapping with temporary variable:")
print("a :", a)
print("b :", b)


a = 10
b = 20
a = a + b
b = a - b
a = a - b
print("After swapping without temporary variable:")
print("a :", a)
print("b :", b)

''' Output:
After swapping with temporary variable:
a : 20
b : 10
After swapping without temporary variable:
a : 20
b : 10
'''