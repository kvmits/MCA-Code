#WAP to check if a string starts and ends with "python"

import re

s = input("Enter a string: ")

if re.search(r"^python.*python$", s):
    print("The string starts and ends with 'python'.")
else:
    print("The string does not start and end with 'python'.")