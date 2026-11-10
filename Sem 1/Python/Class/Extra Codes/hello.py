#WAP to search for "hello" in a given string

import re

s = input("Enter a string: ")

if re.search(r"hello", s):
    print("The string contains the word 'hello'.")
else:
    print("The string does not contain the word 'hello'.")
    
