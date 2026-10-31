#Write a program to check whether a given year is a leap year or not.

year = 2024
if (year % 400 == 0) or (year % 4 == 0 and year % 100 != 0):
    print(year, "is a leap year.")
else:
    print(year, "is not a leap year.")

''' Output:

2024 is a leap year.
'''
