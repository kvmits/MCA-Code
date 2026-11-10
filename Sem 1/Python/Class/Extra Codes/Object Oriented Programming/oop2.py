#write a prgoram to create a class employee with a constructor to initialize employee id name and salary dispaly the details using a method

class employee:
    def __init__(self):
        self.eid = int(input("ID?:"))
        self.name = input("Name?:")
        self.salary = int(input("Salary?:"))
        
    def display(self):
        print(self.eid)
        print(self.name)
        print(self.salary)
        


e1 = employee()
e1.display()
    
    
    
    
    
    
