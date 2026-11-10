#wap to accept mark and rase expensition if marks are not ebtweenn zero and hundred

try:
    marks = int(input("Enter marks (0-100): "))
    if marks < 0 or marks > 100:
        raise ValueError("Marks must be between 0 and 100.")
    print("You entered:", marks)
except ValueError as e:
    print("Error:", e)
    