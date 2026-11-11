# 4. Method Overriding and Polymorphism: Write a Python program to
# demonstrate method overriding using a base class Employee and derived
# classes PermanentEmployee and ContractEmployee. Override the method
# calculate_salary() to calculate salary differently.


class Employee:
    def __init__(self, name):
        self.name = name

    def calculate_salary(self):
        raise NotImplementedError("Subclasses must implement calculate_salary().")


class PermanentEmployee(Employee):
    def __init__(self, name, basic_salary, allowance):
        super().__init__(name)
        self.basic_salary = basic_salary
        self.allowance = allowance

    def calculate_salary(self):
        return self.basic_salary + self.allowance


class ContractEmployee(Employee):
    def __init__(self, name, hours_worked, hourly_rate):
        super().__init__(name)
        self.hours_worked = hours_worked
        self.hourly_rate = hourly_rate

    def calculate_salary(self):
        return self.hours_worked * self.hourly_rate


permanent = PermanentEmployee(
    input("Enter permanent employee name: "),
    float(input("Enter basic salary: ")),
    float(input("Enter allowance: ")),
)
contract = ContractEmployee(
    input("\nEnter contract employee name: "),
    float(input("Enter hours worked: ")),
    float(input("Enter hourly rate: ")),
)

for employee in (permanent, contract):
    print(employee.name, "salary:", round(employee.calculate_salary(), 2))


'''Output:
Enter permanent employee name: Alice
Enter basic salary: 50000
Enter allowance: 5000

Enter contract employee name: Bob
Enter hours worked: 160
Enter hourly rate: 250
Alice salary: 55000.0
Bob salary: 40000.0
'''