# 5. Objects as Arguments: Write a Python program to create a class Rectangle
# with attributes length and breadth. Write a function that accepts two
# Rectangle objects as arguments and compares their areas.


class Rectangle:
    def __init__(self, length, breadth):
        self.length = length
        self.breadth = breadth

    def area(self):
        return self.length * self.breadth


def compare_areas(rectangle1, rectangle2):
    if rectangle1.area() > rectangle2.area():
        return "The first rectangle has the larger area."
    if rectangle2.area() > rectangle1.area():
        return "The second rectangle has the larger area."
    return "Both rectangles have equal areas."


print("Enter dimensions for the first rectangle:")
rectangle1 = Rectangle(
    float(input("Length: ")),
    float(input("Breadth: ")),
)

print("\nEnter dimensions for the second rectangle:")
rectangle2 = Rectangle(
    float(input("Length: ")),
    float(input("Breadth: ")),
)

print("\nFirst rectangle area:", rectangle1.area())
print("Second rectangle area:", rectangle2.area())
print(compare_areas(rectangle1, rectangle2))


'''
Output:
Enter dimensions for the first rectangle:
Length: 5
Breadth: 4

Enter dimensions for the second rectangle:
Length: 3
Breadth: 6

First rectangle area: 20.0
Second rectangle area: 18.0
The first rectangle has the larger area.
'''
