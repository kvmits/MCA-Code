# 9. Accept an email address from the user. Use the re module to check whether
# it follows a valid basic email format. Display whether the email is valid or
# invalid.

import re

email = input("Enter an email address: ").strip()
email_pattern = r"[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}"

if re.fullmatch(email_pattern, email):
	print("Valid email address.")
else:
	print("Invalid email address.")

'''
Output:
Enter an email address: student@example.com
Valid email address.
'''
