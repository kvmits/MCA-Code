# Question: Write a Python program to create a Rectangle class with attributes length and breadth and methods to calculate and display its area and perimeter.
# Module: MOD4
# Section: Introduction_to_OOP

# MOD4 - Introduction_to_OOP: Question 2
# Write your Python program here.

# Example skeleton:
# print('Hello')


class Rectangle():
    def __init__(self,l,b):
        self.l = l
        self.b = b
        
    def area(self):
        print(self.l*self.b)
    
    def perimeter(self):
        print(2*(self.l+self.b))
        
        
obj1 = Rectangle(5,6)
obj1.area()
obj1.perimeter()
#print("Length:",obj1.l)
        