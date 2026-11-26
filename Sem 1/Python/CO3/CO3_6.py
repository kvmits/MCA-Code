# 6. Accept a directory name from the user. Create the directory if it does not
# exist. Rename or remove the directory based on the user's choice.

import os

directory = input("Enter a directory name: ")

if not os.path.exists(directory):
	os.makedirs(directory)
	print(f"Created directory '{directory}'.")
elif not os.path.isdir(directory):
	print("A file with that name already exists.")
	raise SystemExit
else:
	print(f"Directory '{directory}' already exists.")

choice = input("Enter 'r' to rename, 'd' to remove, or anything else to keep it: ").lower()

if choice == "r":
	new_name = input("Enter the new directory name: ")
	try:
		os.rename(directory, new_name)
		print(f"Renamed directory to '{new_name}'.")
	except OSError as error:
		print(f"Could not rename the directory: {error}")
elif choice == "d":
	try:
		os.rmdir(directory)
		print(f"Removed directory '{directory}'.")
	except OSError as error:
		print(f"Could not remove the directory: {error}")
else:
	print("Directory left unchanged.")

'''
Output:
Enter a directory name: sample_folder
Created directory 'sample_folder'.
Enter 'r' to rename, 'd' to remove, or anything else to keep it: d
Removed directory 'sample_folder'.
'''
