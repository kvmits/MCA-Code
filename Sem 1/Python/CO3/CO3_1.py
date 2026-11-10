# 1. Accept n item records containing item number, item name, and price. Store the
# records in a text file. Read and display all the records.


f = open("CO3_1.txt", "w")
n = int(input("Enter the number of items: "))
for i in range(n):
    number = input("Enter item number: ")
    name = input("Enter item name: ")
    price = input("Enter price: ")
    push = number + "," + name + "'" + price
    f.write(push)
f.close()

t = open("items.txt","r")

content = t.readlines()

print(content)
    
    