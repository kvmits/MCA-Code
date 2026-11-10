#using achandimcis and score DERIVE THE CLASSS RESULT DO CALCUALTE AND DISPLAY TOTAL MARKS

class achadamic:
    def get_achadamic_marks(self):
        self.achadamic = int(input("Enter achadamic marks: "))
        return self.achadamic

#base class 2
class sports:
    def get_sports_marks(self):
        self.sports = int(input("Enter sports marks: "))
        return self.sports
    
#derive the class

class result(achadamic, sports):
    def total_marks(self):
        self.total = self.achadamic + self.sports
        print("Total marks:", self.total)
        

#create object of derived class
r = result()
r.get_achadamic_marks()
r.get_sports_marks()
r.total_marks()



