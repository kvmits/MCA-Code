# 7. Accept two numbers from the user and perform division. Handle
# ZeroDivisionError if the denominator is zero. Handle ValueError if the user
# enters non-numeric data.

try:
	numerator = float(input("Enter the numerator: "))
	denominator = float(input("Enter the denominator: "))
	result = numerator / denominator
except ValueError:
	print("Please enter numeric values.")
except ZeroDivisionError:
	print("The denominator cannot be zero.")
else:
	print("Result:", result)

'''
Output:
Enter the numerator: 12
Enter the denominator: 3
Result: 4.0
'''
