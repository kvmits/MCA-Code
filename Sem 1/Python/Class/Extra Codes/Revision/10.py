#create a class product with a constrictor to initialize 
#product_id product_name and qty write a method to calculate and display
#the total cost based on qty and unit price


class product():
    def __init__(self,product_id,product_name,qty,price):
        self.product_id = product_id
        self.product_name = product_name
        self.price = price
        self.qty = qty
        
    def calculate(self):
        final_price = self.qty * self.price
        print(final_price)
        
        
p1 = product(10,"Rice",10,200)

p1.calculate()