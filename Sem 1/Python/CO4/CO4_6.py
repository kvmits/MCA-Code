# 6. Objects as Return Values: Write a Python program to create a class
# Employee with attributes name and salary. Write a function that accepts two
# Employee objects and returns the object having the higher salary. Display
# the details of the returned object.


class Employee:
    def __init__(self, name, salary):
        self.name = name
        self.salary = salary

    def display_details(self):
        print("\nEmployee with the higher salary")
        print("Name:", self.name)
        print("Salary:", self.salary)


def higher_salary_employee(employee1, employee2):
    if employee1.salary >= employee2.salary:
        return employee1
    return employee2


employee1 = Employee(
    input("Enter first employee name: "),
    float(input("Enter first employee salary: ")),
)
employee2 = Employee(
    input("\nEnter second employee name: "),
    float(input("Enter second employee salary: ")),
)

higher_salary_employee(employee1, employee2).display_details()

'''
Output:
Enter first employee name: Alice
Enter first employee salary: 50000

Enter second employee name: Bob
Enter second employee salary: 60000

Employee with the higher salary
Name: Bob
Salary: 60000.0
'''
