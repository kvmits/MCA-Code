#Write a program to calculate the sum of numbers from 1 to N while skipping multiples of 5.

n = 20
total = 0
for num in range(1, n + 1):
    if num % 5 == 0:
        continue
    total += num
print("Sum from 1 to", n, "while skipping multiples of 5:", total)

''' Output:

Sum from 1 to 20 while skipping multiples of 5: 160
'''
