# 10. Create a package graphics with modules rectangle, circle and sub-package 3D-graphics
# with modules cuboid and sphere. Include methods to find area and perimeter of respective
# figures in each module. Write a program that finds area and perimeter of figures by using
# import statements.

from graphics import circle, rectangle
from graphics.three_d_graphics import cuboid, sphere


print("Rectangle area:", rectangle.area(10, 5))
print("Rectangle perimeter:", rectangle.perimeter(10, 5))
print("Circle area:", circle.area(7))
print("Circle perimeter:", circle.perimeter(7))
print("Cuboid surface area:", cuboid.area(10, 5, 3))
print("Cuboid total edge length:", cuboid.perimeter(10, 5, 3))
print("Sphere surface area:", sphere.area(7))
print("Sphere circumference:", sphere.perimeter(7))

''' Output:

Rectangle area: 50
Rectangle perimeter: 30
Circle area: 153.93804002589985
Circle perimeter: 43.982297150257104
Cuboid surface area: 190
Cuboid total edge length: 72
Sphere surface area: 615.7521601035994
Sphere circumference: 43.982297150257104
'''
