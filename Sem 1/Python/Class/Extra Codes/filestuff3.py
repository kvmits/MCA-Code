#WAP to accept n student records roll name age store them in a file and display the contents of the file

n = int(input("Enter the number of students: "))

with open("students2.txt", "a") as f:
    for i in range(n):
        roll = input("Enter roll number: ")
        name = input("Enter name: ")
        age = input("Enter age: ")
        push = roll + ", " + name + ", " + age + "\n"
        f.write(push)

with open("students2.txt", "r") as f:
    content = f.read()
print("Contents of the file:")
print(content)




