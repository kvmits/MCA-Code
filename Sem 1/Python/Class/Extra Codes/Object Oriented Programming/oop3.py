#write to program with constructor with roll, name, age

class Student:
    def __init__(self, roll, name, age):
        self.roll = roll
        self.name = name
        self.age = age

s1 = Student(1, "Alice", 20)
s2 = Student(2, "Bob", 22)

print("Student 1:")
print("Roll:", s1.roll)
print("Name:", s1.name)
print("Age:", s1.age)

print("Student 2:")
print("Roll:", s2.roll)
print("Name:", s2.name)
print("Age:", s2.age)