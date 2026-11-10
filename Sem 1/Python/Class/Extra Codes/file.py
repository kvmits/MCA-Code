#write a program to append a students roll number name and age to an existing file named "students.txt"

#write a program to read a text file and count the number of lines present in it

#write a program to read a text file and count the number of words in it

#write a program to read a text file and count the number of vowels in it


while True:
    print("1.Add 2.Count Lines 3.Count Words 4.Count Vowels 5.Display 6.Exit")
    ch = int(input("Enter your choice: "))
    if ch == 1:
        roll = input("Enter roll number: ")
        name = input("Enter name: ")
        age = input("Enter age: ")
        with open("students.txt", "a") as f:
            push = roll + ", " + name + ", " + age + "\n"
            f.write(push)
    elif ch == 2:
        with open("sample.txt", "r") as f:
            content = f.read()
        lines = len(content.splitlines())
        print("Number of lines in the f:", lines)
    elif ch == 3:
        with open("sample.txt", "r") as f:
            content = f.read()
        words = len(content.split())
        print("Number of words in the f:", words)
    elif ch == 4:
        with open("sample.txt", "r") as f:
            content = f.read()
        vowels = sum(char in "aeiouAEIOU" for char in content)
        print("Number of vowels in the f:", vowels)
    elif ch == 5:
        with open("students.txt", "r") as f:
            content = f.read()
        print("Contents of the file:")
        print(content)
    elif ch == 6:
        break
    else:
        print("Invalid choice")
