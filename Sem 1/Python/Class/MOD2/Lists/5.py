# Question: Write a Python program to create a list of numbers and, using list comprehension, generate separate lists containing even numbers and odd numbers.
# Module: MOD2
# Section: Lists

# MOD2 - Lists: Question 5
# Write your Python program here.

# Example skeleton:
# print('Hello')


L = [1,2,3,4,5,6,7,8,9,10]

E = [i for i in L if i%2==0]

O = [i for i in L if i%2!=0]

print(E)
print(O)
