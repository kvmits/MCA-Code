# Question: Write a Python program to copy the contents of one text file to another file.
# Module: MOD3
# Section: File_Handling

# MOD3 - File_Handling: Question 4
# Write your Python program here.

# Example skeleton:
# print('Hello')

with open("student.txt", "r") as f:
    content = f.read()

with open("studentcopy.txt", "w") as f:
    f.write(content)
