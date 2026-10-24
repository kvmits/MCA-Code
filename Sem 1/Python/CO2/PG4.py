# 4. Write a Python program that accepts a tuple of elements from the user and performs
# the following important tuple operations:
# a) Find the sum and average of numeric elements.
# b) Count the occurrences of a specified element using count().
# c) Find the index of a specified element using index().
# d) Check whether a specified element exists in the tuple.
# e) Access and display elements using indexing.
# f) Display elements using slicing.
# g) Display the tuple in reverse order.
# h) Concatenate the tuple with another tuple.
# i) Repeat the tuple using the * operator.
# j) Convert the tuple into a list, modify it, and convert it back to a tuple.
# k) Find the second largest and second smallest elements.
# l) Count the number of even and odd elements.
# m) Create a new tuple containing the squares of all numeric elements.
# n) Find the common elements between two tuples.
# o) Remove duplicate elements by creating a tuple containing only unique elements.

values = tuple(float(value) for value in input("Enter numeric tuple elements: ").split())
print("Sum:", sum(values))
print("Average:", sum(values) / len(values))

specified = float(input("Enter an element to count and find: "))
print("Occurrences:", values.count(specified))
print("Index:", values.index(specified) if specified in values else "Not found")
print("Exists:", specified in values)
if values:
    print("First element:", values[0])
print("Slice:", values[: len(values) // 2])
print("Reverse:", values[::-1])

other = tuple(float(value) for value in input("Enter another tuple: ").split())
print("Concatenated:", values + other)
print("Repeated:", values * 2)

modified = list(values)
if modified:
    modified[0] = float(input("Enter a replacement for the first element: "))
modified.append(float(input("Enter an element to add: ")))
print("Modified tuple:", tuple(modified))

distinct = sorted(set(values))
if len(distinct) >= 2:
    print("Second smallest:", distinct[1])
    print("Second largest:", distinct[-2])
else:
    print("At least two distinct elements are required for second smallest/largest.")
print("Even count:", sum(value % 2 == 0 for value in values))
print("Odd count:", sum(value % 2 != 0 for value in values))
print("Squares:", tuple(value ** 2 for value in values))
print("Common elements:", tuple(dict.fromkeys(value for value in values if value in other)))
print("Unique elements:", tuple(dict.fromkeys(values)))

''' Output:

Enter numeric tuple elements: 1 2 3 2 4
Sum: 12.0
Average: 2.4
Occurrences: 2
Index: 1
Exists: True
First element: 1.0
Slice: (1.0, 2.0)
Reverse: (4.0, 2.0, 3.0, 2.0, 1.0)
'''
