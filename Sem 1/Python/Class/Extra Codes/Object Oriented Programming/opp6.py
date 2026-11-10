#write a program to write an handle exepcetion orrcurs when the secodn number is 0


num1 = int(input("Enter first number: "))
num2 = int(input("Enter second number: "))
try:
    result = num1 / num2
    print("Result:", result)
except ZeroDivisionError:
    print("Error: Cannot divide by zero.")  
    

