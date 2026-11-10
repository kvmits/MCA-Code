#Program to swap 2 varibles without using a third variable

x = 10
y = 20
print("Before")
print(x)
print(y)

x = x + y
y = x - y
x = x - y
print("After")

print(x)
print(y)
