#WAP to see if a string ends with "python"

import re

s = input("Enter a string: ")

if re.search(r"python$", s):
    print("The string ends with 'python'.")
else:
    print("The string does not end with 'python'.")