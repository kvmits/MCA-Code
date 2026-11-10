#Program to create a wallet class with add and spend methods

class wallet:
    def __init__(self, balance):
        self.balance = balance

    def add(self):
        amount = int(input("Enter amount to add:"))
        self.balance = self.balance + amount
        print("Added ",amount,"New balance: ",self.balance)

    def spend(self):
        amount = int(input("Enter amount to spend:"))
        if amount > self.balance:
            print("Insufficient funds!")
        else:
            self.balance = self.balance - amount
            print("Spent" ,amount,"New balance:",self.balance)
            
user1 = wallet(0)
while True:
    print("1.Add 2.Spend 3.Exit")
    ch = int(input("Enter your choice:"))
    if ch == 1:
        user1.add()
    elif ch == 2:
        user1.spend()
    elif ch == 3:
        break
    else:
        print("Invalid choice!")
        
        