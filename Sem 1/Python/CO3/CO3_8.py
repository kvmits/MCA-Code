# 8. Write a Python program to accept the marks obtained by a student in three
# subjects and calculate and display the average marks. The program should use
# exception handling to handle invalid (non-numeric) input. It should also raise
# an appropriate exception if any mark entered is less than 0 or greater than
# 100. Display a suitable error message when an exception occurs.

try:
	marks = []
	for subject_number in range(1, 4):
		mark = float(input(f"Enter marks for subject {subject_number}: "))
		if not 0 <= mark <= 100:
			raise ValueError("Marks must be between 0 and 100.")
		marks.append(mark)

	average = sum(marks) / len(marks)
except ValueError as error:
	print("Invalid input:", error)
else:
	print(f"Average marks: {average:.2f}")

'''
Output:
Enter marks for subject 1: 80
Enter marks for subject 2: 90
Enter marks for subject 3: 100
Average marks: 90.00
'''
