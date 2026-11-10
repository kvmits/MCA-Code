# 3. Read a text file. Find and display the number of lines, words, and characters
# in the file.

count = 0

f = open("CO3_3.txt","r")
content = f.readlines()
print("Lines:",len(content))
f = open("CO3_3.txt","r")
content = f.read()
words = len(content.split())
print("Words:",words)
f = open("CO3_3.txt","r")
content = f.read()
for char in content:
    count = count + 1
print("Characters:",count)
f.close()

