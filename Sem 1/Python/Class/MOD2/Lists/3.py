# Question: Write a Python program to create a nested list representing marks of students in different subjects and display the marks of a particular student.
# Module: MOD2
# Section: Lists

# MOD2 - Lists: Question 3
# Write your Python program here.

# Example skeleton:
# print('Hello')


# Sample Student = ["Walter","25","12","B",[59,45,56,51,52]]

S = []

S.append(input("Enter the name:"))
S.append(int(input("Enter the Roll:")))
S.append(int(input("Enter the Class:")))
S.append(input("Enter the Division:"))

mark = []

for i in range(1,6):
    mark.append(int(input("Enter the mark of "+str(i)+" Subject:")))

S.append(mark)

print(S)