#Write a program to do Fibbonacci series till n number

n = int(input("Enter the number of values: "))

a = 0
b = 1

print(a, b, end=" ")

for _ in range(2, n):
    last = a + b
    print(last, end=" ")
    a = b
    b = last

