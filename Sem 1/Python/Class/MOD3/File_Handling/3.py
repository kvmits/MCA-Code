# Question: Write a Python program to count the number of lines, words, and characters in a text file.
# Module: MOD3
# Section: File_Handling

# MOD3 - File_Handling: Question 3
# Write your Python program here.

# Example skeleton:
# print('Hello')


with open("student.txt", "r") as f:
    content = f.read()
    lines = len(content.split('\n'))
    words = len(content.split())
    characters = len(content)
    
    print("Lines:",lines)
    print("Words:",words)
    print("Characters:",characters)
    
    