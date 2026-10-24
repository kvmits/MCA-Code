# 9. Create a Python program that stores book titles in a list. The program should allow the
# user to:
#  Add a new book.
#  Remove a book.
#  Search for a book by title.
#  Display all books.
#  Count how many books contain a particular word.
#  Display the longest book title.

books = []

while True:
    print("\n1. Add  2. Remove  3. Search  4. Display all")
    print("5. Count titles containing a word  6. Display longest title  7. Exit")
    ch = input("Choose an option: ")

    if ch == "1":
        books.append(input("Enter the book title: "))
    elif ch == "2":
        title = input("Enter the title to remove: ")
        if title in books:
            books.remove(title)
        else:
            print("Book not found.")
    elif ch == "3":
        title = input("Enter the title to search for: ")
        print("Book found." if title in books else "Book not found.")
    elif ch == "4":
        print("Books:", books)
    elif ch == "5":
        word = input("Enter a word: ").casefold()
        count = sum(word in title.casefold() for title in books)
        print("Matching titles:", count)
    elif ch == "6":
        print("Longest title:", max(books, key=len) if books else "No books available.")
    elif ch == "7":
        break
    else:
        print("Invalid choice.")

''' Output:

1. Add  2. Remove  3. Search  4. Display all
5. Count titles containing a word  6. Display longest title  7. Exit
Choose an option: 1
Enter the book title: Python Programming
Choose an option: 4
Books: ['Python Programming']
Choose an option: 7
'''
