# Question: Write a Python program to create a text file, write student details into it, and read and display its contents using the with statement.
# Module: MOD3
# Section: File_Handling

# MOD3 - File_Handling: Question 1
# Write your Python program here.

# Example skeleton:
# print('Hello')


with open("student.txt", "w") as f:
    f.write("Name: John Doe\nAge: 20\nMajor: Computer Science\n")

with open("student.txt", "r") as f:
    contents = f.read()
    print(contents)
    

