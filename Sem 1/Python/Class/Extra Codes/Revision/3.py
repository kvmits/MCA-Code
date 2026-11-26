# write a program to didsplay a number in the following pattern 
# 	1
# 	1 2
# 	1 2 3
# 	1 2 3 4
# 	1 2 3 4 5

    
for i in range(1,7):
    for j in range(1,i):
        print(j," ",end="")
    print("")