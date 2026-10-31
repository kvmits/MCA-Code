# 3. Write a Python program that accepts a list of numbers from the user and performs the
# following operations:
# a) Find the length of the list.
# b) Display the largest and smallest elements.
# c) Find the sum and average of the elements.
# d) Count the occurrences of a specified element.
# e) Find the index of a specified element.
# f) Add an element using append().
# g) Insert an element at a specified position using insert().
# h) Remove a specified element using remove().
# i) Remove the last element using pop().
# j) Sort the list in ascending and descending order.
# k) Reverse the list.
# l) Create a list containing only unique elements.
# m) Find the second largest and second smallest elements.
# n) Check whether a specified element exists in the list.
# o) Display the list using slicing (first half, last half, etc.).
# p) Create a new list containing the square of each element.
# q) Separate the elements into even and odd lists. Display the two lists.

num = [float(val) for val in input("Enter numbers separated by spaces: ").split()]
print("Length:", len(num))
print("Largest:", max(num))
print("Smallest:", min(num))
print("Sum:", sum(num))
print("Average:", sum(num) / len(num))
specified = float(input("Enter an element to count and find: "))
print("Occurrences:", num.count(specified))
print("Index:", num.index(specified) if specified in num else "Not found")

num.append(float(input("Enter an element to append: ")))
position = int(input("Enter the insert position: "))
num.insert(position, float(input("Enter an element to insert: ")))

remove_value = float(input("Enter an element to remove: "))
if remove_value in num:
    num.remove(remove_value)
else:
    print("Element not found; nothing was removed.")
if num:
    print("Popped element:", num.pop())

print("Ascending:", sorted(num))
print("Descending:", sorted(num, reverse=True))
num.reverse()
print("Reversed:", num)

unique = list(dict.fromkeys(num))
print("Unique elements:", unique)
distinct = sorted(set(num))
if len(distinct) >= 2:
    print("Second smallest:", distinct[1])
    print("Second largest:", distinct[-2])
else:
    print("At least two distinct elements are required for second smallest/largest.")

specified = float(input("Enter an element to search: "))
print("Exists:", specified in num)
middle = len(num) // 2
print("First half:", num[:middle])
print("Last half:", num[middle:])
print("Squares:", [number ** 2 for number in num])
print("Even:", [number for number in num if number % 2 == 0])
print("Odd:", [number for number in num if number % 2 != 0])

''' Output:

Enter numbers separated by spaces: 1 2 3 4 5
Length: 5
Largest: 5.0
Smallest: 1.0
Sum: 15.0
Average: 3.0
'''
