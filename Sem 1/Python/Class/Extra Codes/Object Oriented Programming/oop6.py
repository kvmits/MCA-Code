#write a program to demonstrate single inhericne
#create a parent class person with a method to display the name
#create a child class Student that inherits from person and displays the roll number


class Person:
    def __init__(self, name):
        self.name = name
        
    def display_name(self):
        print("Name:", self.name)
        
class Student(Person):
    def __init__(self, name, roll_number):
        super().__init__(name)
        self.roll_number = roll_number
        
    def display_roll_number(self):
        print("Roll Number:", self.roll_number)
        

s1 = Student("Alice", 101)
s1.display_name()
s1.display_roll_number()


