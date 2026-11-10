#WAP to find all digits in a string

import re

s = input("Enter a string: ")

if re.search(r"\d", s):
    print("The string contains digits.")
    digits = re.findall(r"\d", s)
    print("Digits found in the string:", digits)
else:
    print("The string does not contain any digits.")
    
    