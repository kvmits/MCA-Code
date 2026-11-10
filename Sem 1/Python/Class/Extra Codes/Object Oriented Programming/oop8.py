#try doing file does not exist error handling

try:
    with open("student.txt", "r") as f:
        content = f.read()
        print(content)
except FileNotFoundError:
    print("Error: The file does not exist.")    
    

