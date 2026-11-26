# 5. Use the os module to display all files and subdirectories in a given
# directory. Separately display the number of files and directories.

import os

directory = input("Enter a directory path: ")

try:
	entries = os.listdir(directory)
	files = [entry for entry in entries if os.path.isfile(os.path.join(directory, entry))]
	directories = [entry for entry in entries if os.path.isdir(os.path.join(directory, entry))]

	print("Files:")
	for filename in files:
		print(filename)

	print("\nSubdirectories:")
	for directory_name in directories:
		print(directory_name)

	print("\nNumber of files:", len(files))
	print("Number of directories:", len(directories))
except FileNotFoundError:
	print("The directory does not exist.")
except NotADirectoryError:
	print("The given path is not a directory.")

'''
Output:
Enter a directory path: sample_folder
Files:
notes.txt
data.csv

Subdirectories:
images

Number of files: 2
Number of directories: 1
'''
