# 2. Encapsulation and Data Hiding: Write a Python program to demonstrate
# encapsulation using a class BankAccount. Create a private variable to store
# the account balance and provide methods to deposit, withdraw and display
# the balance.


class BankAccount:
    def __init__(self, balance=0.0):
        if balance < 0:
            raise ValueError("The opening balance cannot be negative.")
        self.__balance = balance

    def deposit(self, amount):
        if amount <= 0:
            print("Deposit amount must be greater than zero.")
            return
        self.__balance += amount
        print(f"Deposited: {amount:.2f}")

    def withdraw(self, amount):
        if amount <= 0:
            print("Withdrawal amount must be greater than zero.")
        elif amount > self.__balance:
            print("Insufficient balance.")
        else:
            self.__balance -= amount
            print(f"Withdrawn: {amount:.2f}")

    def display_balance(self):
        print(f"Account balance: {self.__balance:.2f}")


account = BankAccount(float(input("Enter opening balance: ")))

while True:
    print("\n1. Deposit")
    print("2. Withdraw")
    print("3. Display balance")
    print("4. Exit")
    choice = input("Enter your choice: ")

    if choice == "1":
        account.deposit(float(input("Enter amount to deposit: ")))
    elif choice == "2":
        account.withdraw(float(input("Enter amount to withdraw: ")))
    elif choice == "3":
        account.display_balance()
    elif choice == "4":
        break
    else:
        print("Invalid choice. Please try again.")
'''
Output:
Enter opening balance: 1000
1. Deposit
2. Withdraw
3. Display balance
4. Exit
Enter your choice: 1
Enter amount to deposit: 500
Deposited: 500.00
1. Deposit
2. Withdraw
3. Display balance
4. Exit
Enter your choice: 3
Account balance: 1500.00
1. Deposit
2. Withdraw
3. Display balance
4. Exit
Enter your choice: 4
'''