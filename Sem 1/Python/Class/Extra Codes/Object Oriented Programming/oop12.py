#demonstrate method overriding using a base class employee and derived classes permanant employee and contract employee
#override the method calculate salary to calculate salary differently 
#Method overiding 

class employee:
    def get_salary(self):
        self.salary = int(input("Enter salary: "))
        return self.salary
