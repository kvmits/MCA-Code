#write a program to create a class employee with name and salary create 2 objects to display thei detials 
#illustration of multiple objets


class employee:
    def __init__(self,name,salary):
        self.name = name
        self.salary = salary
        
    def display(self):
        print(self.name)
        print(self.salary)
        
e1 = employee("John",50000)
e2 = employee("Alice",60000)