# 2. Create a dictionary of 5 student names with their marks.
# “Anu&quot;: 85, &quot;Ravi&quot;: 90, &quot;Minu&quot;: 75, &quot;Sara&quot;: 88, &quot;Tom&quot;: 94
#
# a) Access the value of the key Sara
# b) Add a new student &quot;Kiran&quot;: 80 to the dictionary and update &quot;Minu&quot;’s marks to 82.
# c) Delete &quot;Tom&quot; from the dictionary.
# d) Display the names of all students in the dictionary.
# e) Print all keys and values separately.
# f) Sort the dictionary by values in ascending order
# g) Sort the dictionary by keys in ascending order
# h) Display the student with highest marks.
# i) Create another dictionary “Anusha&quot;: 85, &quot;Navin&quot;: 70, &quot;Libin&quot;: 75. Merge the two
# dictionaries

s = {"Anu": 85, "Ravi": 90, "Minu": 75, "Sara": 88, "Tom": 94}

print("Marks of Sara:", s["Sara"])
s["Kiran"] = 80
s["Minu"] = 82
del s["Tom"]

print("Student names:", list(s))
print("Keys:", list(s.keys()))
print("Values:", list(s.values()))
print("Sorted by values:", dict(sorted(s.items(), key=lambda item: item[1])))
print("Sorted by keys:", dict(sorted(s.items())))

highest_student = max(s, key=s.get)
print("Student with highest marks:", highest_student, s[highest_student])

other_students = {"Anusha": 85, "Navin": 70, "Libin": 75}
s.update(other_students)
print("Merged dictionary:", s)

''' Output:

Marks of Sara: 88
Student names: ['Anu', 'Ravi', 'Minu', 'Sara', 'Kiran']
Keys: ['Anu', 'Ravi', 'Minu', 'Sara', 'Kiran']
Values: [85, 90, 82, 88, 80]
Sorted by values: {'Kiran': 80, 'Minu': 82, 'Anu': 85, 'Sara': 88, 'Ravi': 90}
Sorted by keys: {'Anu': 85, 'Kiran': 80, 'Minu': 82, 'Ravi': 90, 'Sara': 88}
Student with highest marks: Ravi 90
Merged dictionary: {'Anu': 85, 'Ravi': 90, 'Minu': 82, 'Sara': 88, 'Kiran': 80, 'Anusha': 85, 'Navin': 70, 'Libin': 75}
'''
