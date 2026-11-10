# Question: Write a Python program to count the occurrences of a specified element in a tuple and find its position using tuple methods.
# Module: MOD2
# Section: Tuples

# MOD2 - Tuples: Question 4
# Write your Python program here.

# Example skeleton:
# print('Hello')



tup = (1,2,3,4,5,6,7,8,9,10,5)

x = int(input("Enter the element to look for :"))
count , ind = 0 , 0

for i in tup:
    if x == i:
        print(ind)
        count = count + 1
    ind = ind + 1
    
print("Count:",count)