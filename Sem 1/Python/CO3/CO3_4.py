# 4. Accept a word from the user. Search for the word in a text file. Display
# whether the word is found and the number of times it occurs.

import re

word = input("Enter the word to search for: ").strip()

with open("CO3_3.txt", "r") as text_file:
	contents = text_file.read()

matches = re.findall(rf"\b{re.escape(word)}\b", contents, flags=re.IGNORECASE)
if matches:
	print(f"The word '{word}' was found {len(matches)} time(s).")
else:
	print(f"The word '{word}' was not found.")

'''
Output:
Enter the word to search for: Test
The word 'Test' was found 2 time(s).
'''
