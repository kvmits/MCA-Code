#Menu Drivern Program to take 2 numbers from the user and do the following with exit
#Sum , diff, pro , div , power , find area.

while True:
	
	a = int(input("Enter the value for A:"))
	b = int(input("Enter the value for B:"))
	
	ch = int(input("1.Add,2.Sub,3.Mul,4.Div,5.Power,6.Area,7.Exit"))
	
	if (ch == 1):
		print("The Sum of 2 numbers is:",a+b)
	elif (ch == 2):
		print("The Differnce is 2 numbers is:",a-b)
	elif (ch == 3):
		print("The Product is 2 numbers is:",a*b)
	elif (ch == 4):
		print("The Division is 2 numbers is:",a/b)
	elif (ch == 5):
		print("The Power is 2 numbers is:",a**b)
	elif (ch == 6):
		print("The Area is:",a*b)
	elif (ch == 7):
		break
	else:
		print("The Entered Value is invalid, Try Agian")
