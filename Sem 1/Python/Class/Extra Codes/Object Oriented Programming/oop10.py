#raise invalid age error for age not negative and 0

try:
    age = int(input("Enter your age: "))
    if age <= 0:
        raise ValueError("Invalid age. Age must be a positive number.")
    print("Your age is:", age)
except ValueError as e:
    print("Error:", e)
    
    

    
    