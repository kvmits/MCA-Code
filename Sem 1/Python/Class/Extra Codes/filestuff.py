#WAP to create a file named Sample.txt and write 3 liens of text 
#then display a message indicating that the file has been created sucessfully

f = open("sample.txt", "w")

f.write("This is line 1 of the file\nThis is line 2 of the file\nThis is line 3 of the file\n")

f.close()

print("File has been created successfully!")