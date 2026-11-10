# Question: Write a Python program to create a Student class with attributes such as name, roll number, and marks, and a method to display the student details.
# Module: MOD4
# Section: Introduction_to_OOP

# MOD4 - Introduction_to_OOP: Question 1
# Write your Python program here.

# Example skeleton:
# print('Hello')


class Student:
    def __init__(self, name, roll, marks):
        self.name = name
        self.roll = roll
        self.marks = marks

    def display_details(self):
        print("Student Name: ", self.name)
        print("Roll Number: ", self.roll)
        print("Marks: ", self.marks)

s1 = Student("Alice", "A001", 85)
s1.display_details()


    