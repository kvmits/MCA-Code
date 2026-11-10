#create a package graphics with modules rectangle , circle and subpackage graphics3D with modules cuboid and sphere
#include methods to find area and perimeter of respective figures in each module
#use import statements for import of modules
#write a simple menu driven program to do each module's respective operations
    
import graphics.rectangle, graphics.circle, graphics3d.cuboid, graphics3d.sphere

#from graphics import rectangle, circle (old way)

len = float(input("Enter length: "))
bre = float(input("Enter breadth: "))
hei = float(input("Enter height: "))
radius = float(input("Enter radius: "))

print("Area of Rectangle:", graphics.rectangle.area(len, bre))
print("Perimeter of Rectangle:", graphics.rectangle.perimeter(len, bre))
print("Area of Circle:", graphics.circle.area(radius))
print("Perimeter of Circle:", graphics.circle.perimeter(radius))
print("Surface Area of Cuboid:", graphics3d.cuboid.area(len, bre, hei))
print("Volume of Cuboid:", graphics3d.cuboid.volume(len, bre, hei))
print("Surface Area of Sphere:", graphics3d.sphere.area(radius))
print("Volume of Sphere:", graphics3d.sphere.volume(radius))

'''
ch = 0

while ch != 5:
    print("1. Area and Perimeter of Rectangle; 2. Area and Perimeter of Circle; 3. Surface Area and Volume of Cuboid; 4. Surface Area and Volume of Sphere; 5. Exit")
    
    ch = int(input("Enter your choice: "))
    
    if ch == 1:
        len = float(input("Enter length: "))
        bre = float(input("Enter breadth: "))
        print("Area of Rectangle:", graphics.rectangle.area(len, bre))
        print("Perimeter of Rectangle:", graphics.rectangle.perimeter(len, bre))
        
    elif ch == 2:
        radius = float(input("Enter radius: "))
        print("Area of Circle:", graphics.circle.area(radius))
        print("Perimeter of Circle:", graphics.circle.perimeter(radius))
        
    elif ch == 3:
        len = float(input("Enter length: "))
        bre = float(input("Enter breadth: "))
        hei = float(input("Enter height: "))
        print("Surface Area of Cuboid:", graphics3d.cuboid.area(len, bre, hei))
        print("Volume of Cuboid:", graphics3d.cuboid.volume(len, bre, hei))
        
    elif ch == 4:
        radius = float(input("Enter radius: "))
        print("Surface Area of Sphere:", graphics3d.sphere.area(radius))
        print("Volume of Sphere:", graphics3d.sphere.volume(radius))
        
    elif ch == 5:
        print("Exiting...")
        
    else:
        print("Invalid choice!")

'''

