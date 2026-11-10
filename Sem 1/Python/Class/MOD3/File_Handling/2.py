# Question: Write a Python program to append new records to an existing text file and display the updated contents.
# Module: MOD3
# Section: File_Handling

# MOD3 - File_Handling: Question 2
# Write your Python program here.

# Example skeleton:
# print('Hello')


f = open("student.txt", "a")
f = f.write("Roll Number: 23\n")


with open("student.txt", "r") as f:
    contents = f.read()
    print(contents)
    
    
f.close()