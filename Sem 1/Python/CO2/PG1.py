# 1. Write a Python program that accepts a sentence as a strin from the user and performs
# the following operations on the given string:
# a) Find the length of the string.
# b) Count the number of vowels, consonants, digits, spaces, and special characters.
# c) Convert the string to uppercase and lowercase.
# d) Check whether the string starts and ends with a specified character.
# e) Count the occurrences of a specified character or substring.
# f) Find the first and last occurrence of a specified character.
# g) Replace a specified character/substring with another.
# h) Remove leading and trailing spaces.
# i) Check whether the string is a palindrome.
# j) Split the string into words and display the number of words.
# k) Sort the characters of the string in ascending order.
# l) Display the string after removing duplicate characters.

sentence = input("Enter a sentence: ")

vowels = sum(character.lower() in "aeiou" for character in sentence)
consonants = sum(character.isalpha() and character.lower() not in "aeiou" for character in sentence)
digits = sum(character.isdigit() for character in sentence)
spaces = sum(character.isspace() for character in sentence)
special_characters = sum(
    not character.isalnum() and not character.isspace() for character in sentence
)

print("Length:", len(sentence))
print("Vowels:", vowels)
print("Consonants:", consonants)
print("Digits:", digits)
print("Spaces:", spaces)
print("Special characters:", special_characters)
print("Uppercase:", sentence.upper())
print("Lowercase:", sentence.lower())

specified_character = input("Enter a character to check at the start and end: ")
print("Starts with the character:", sentence.startswith(specified_character))
print("Ends with the character:", sentence.endswith(specified_character))

substring = input("Enter a character or substring to count: ")
print("Occurrences:", sentence.count(substring))
print("First occurrence:", sentence.find(substring))
print("Last occurrence:", sentence.rfind(substring))

replace = input("Enter the replacement text: ")
print("After replacement:", sentence.replace(substring, replace))
print("Without leading/trailing spaces:", sentence.strip())

normalized = "".join(character.lower() for character in sentence if character.isalnum())
print("Palindrome:", normalized == normalized[::-1])

words = sentence.split()
print("Words:", words)
print("Number of words:", len(words))
print("Sorted characters:", "".join(sorted(sentence)))

unique_characters = "".join(dict.fromkeys(sentence))
print("After removing duplicate characters:", unique_characters)

''' Output:

Enter a sentence: Hello World 123!
Length: 16
Vowels: 3
Consonants: 7
Digits: 3
Spaces: 2
Special characters: 1
Uppercase: HELLO WORLD 123!
Lowercase: hello world 123!
Enter a character to check at the start and end: H
Starts with the character: True
Ends with the character: False
'''
