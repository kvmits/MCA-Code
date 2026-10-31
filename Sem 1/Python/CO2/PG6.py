# 6. Write a Python function that accepts a string and counts the number of upper and lower
# case letters.

def count_cases(text):
    upper = sum(character.isupper() for character in text)
    lower = sum(character.islower() for character in text)
    return upper, lower


text = input("Enter a string: ")
upper_count, lower_count = count_cases(text)
print("Uppercase letters:", upper_count)
print("Lowercase letters:", lower_count)

''' Output:

Enter a string: Hello World
Uppercase letters: 2
Lowercase letters: 8
'''
