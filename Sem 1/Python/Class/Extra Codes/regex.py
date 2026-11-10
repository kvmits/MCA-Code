#write a program using regular expression to check weather 
#the given string contins the word pyhton

import re

s = input("Enter a string: ")

if re.search(r"python", s):
    print("The string contains the word 'python'.")
    
else:
    print("The string does not contain the word 'python'.")
    
