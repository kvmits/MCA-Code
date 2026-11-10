# Question: Write a Python program to accept a string and count the number of vowels, consonants, digits, and spaces using string operations and methods.
# Module: MOD2
# Section: Strings

# MOD2 - Strings: Question 5
# Write your Python program here.

# Example skeleton:
# print('Hello')



text = input("Enter a string: ")


vo = 0
con = 0
dig = 0
spaces = 0


for char in text:
    if char.lower() in "aeiou":      
        vo = vo + 1
    elif char.isalpha():            
        con = con + 1
    elif char.isdigit():            
        dig = dig + 1
    elif char.isspace():            
        spaces = spaces + 1


print("Vowels:", vo)
print("Consonants:", con)
print("Digits:", dig)
print("Spaces:", spaces)