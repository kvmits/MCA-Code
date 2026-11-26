# 2. Open an existing student file with data roll number, name, course in append
# mode. Add details of a new student. Display the updated contents of the file.

student_file_name = "students.txt"

with open(student_file_name, "a+") as student_file:
	roll_number = input("Enter roll number: ")
	name = input("Enter student name: ")
	course = input("Enter course: ")
	student_file.write(f"{roll_number},{name},{course}\n")

	student_file.seek(0)
	print("\nUpdated student records:")
	print(student_file.read(), end="")

'''
Output:
Enter roll number: 102
Enter student name: Grace
Enter course: MCA

Updated student records:
101,Ada,Science
102,Grace,MCA
'''
