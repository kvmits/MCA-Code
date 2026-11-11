# 1. Class, Objects and Constructors: Write a Python program to create a class
# Student with attributes roll number, name and marks. Initialize the
# attributes using a constructor and display the student details.


class Student:
    def __init__(self, roll_number, name, marks):
        self.roll_number = roll_number
        self.name = name
        self.marks = marks

    def display_details(self):
        print("\nStudent Details")
        print("Roll number: " , self.roll_number)
        print("Name: " , self.name)
        print("Marks: " ,self.marks )



roll_number = int(input("Enter roll number: "))
name = input("Enter name: ")
marks = float(input("Enter marks: "))
student = Student(roll_number, name, marks)
student.display_details()


'''
Output:
Enter roll number: 101
Enter name: John Doe
Enter marks: 85.5

Student Details
Roll number:  101
Name:  John Doe
Marks:  85.5
'''
