# Question: Write a Python program to store and retrieve student records using binary files and pickling.
# Module: MOD3
# Section: File_Handling

# MOD3 - File_Handling: Question 5
# Write your Python program here.

# Example skeleton:
# print('Hello')

import pickle

with open("student.dat", "wb") as f:
    student = {"Name": "John Doe", "Age": 20, "Major": "Computer Science"}
    pickle.dump(student, f)
    
    
with open("student.dat", "rb") as f:
    student = pickle.load(f)
    print(student)