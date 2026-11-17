#accpet item_number item_detials and price for an item sotre it in a text file read and dispaly all the records 


with open("7.txt","w") as f:
    item_number = input("Enter the Item number")
    item_details = input("Enter the Item Name")
    price = input("Price")
    write = item_number + " " + item_details + " " + price
    f.write(write)
    
    f.close()
    
with open("7.txt","r") as f:
    all = f.readline()
    print(all)