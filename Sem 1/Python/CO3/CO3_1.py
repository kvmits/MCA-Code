# 1. Accept n item records containing item number, item name, and price. Store the
# records in a text file. Read and display all the records.


item_count = int(input("Enter the number of items: "))

with open("CO3_1.txt", "w") as item_file:
    for _ in range(item_count):
        number = input("Enter item number: ")
        name = input("Enter item name: ")
        price = input("Enter price: ")
        item_file.write(f"{number},{name},{price}\n")

with open("CO3_1.txt", "r") as item_file:
    print("\nItem records:")
    print(item_file.read(), end="")

'''
Output:
Enter the number of items: 2
Enter item number: 101
Enter item name: Pen
Enter price: 10
Enter item number: 102
Enter item name: Notebook
Enter price: 50

Item records:
101,Pen,10
102,Notebook,50
'''
    
    