#Check if a email given by the user is valid or not 

email = input("Enter the Email:")


part = email.split("@")
part2 = part[-1].split(".")
part.pop()

email2 = part + part2

print(email2)

if (len(email2) == 3):
    if "@" in email:
        if "." in email:
            print("valid")
        else:
            print("invalid")
    else:
        print("invalid")
else:
    print("invalid")