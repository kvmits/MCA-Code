# 3. Multiple Inheritance: Write a Python program to demonstrate multiple
# inheritance using classes Academic and Sports. Create a derived class Result
# to calculate and display the total marks.


class Academic:
    def __init__(self, academic_marks):
        self.academic_marks = academic_marks


class Sports:
    def __init__(self, sports_marks):
        self.sports_marks = sports_marks


class Result(Academic, Sports):
    def __init__(self, academic_marks, sports_marks):
        Academic.__init__(self, academic_marks)
        Sports.__init__(self, sports_marks)

    def display_result(self):
        total_marks = self.academic_marks + self.sports_marks
        print("\nAcademic marks:", self.academic_marks)
        print("Sports marks:", self.sports_marks)
        print("Total marks:", total_marks)


academic_marks = float(input("Enter academic marks: "))
sports_marks = float(input("Enter sports marks: "))

result = Result(academic_marks, sports_marks)
result.display_result()


'''
Output:
Enter academic marks: 80
Enter sports marks: 20

Academic marks: 80.0
Sports marks: 20.0
Total marks: 100.0
'''
