#wap to create a class student with attirbutes roll, name, mark create a spelling an object and display student detisla using method 

class student():
    def __init__(self, roll, name, age):
        self.roll = roll
        self.name = name
        self.age = age

s1 = student(1, "Alice", 20)
s2 = student(2, "Bob", 22)

print(s1.roll,s1.name,s1.age)

print(s2.roll,s2.name,s2.age)