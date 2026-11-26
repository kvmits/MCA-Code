# 10. Write a Python program using the re module to extract and display all valid
# 10-digit Indian mobile numbers from a given text. The mobile number should
# begin with 6, 7, 8, or 9. Use a suitable regular expression to identify the
# valid mobile numbers.
#
# Sample text: Contact Anu at 9876543210, Rahul at 9123456780 and Meera at 8123456789.

import re

text = "Contact Anu at 9876543210, Rahul at 9123456780 and Meera at 8123456789."
mobile_numbers = re.findall(r"(?<!\d)[6-9]\d{9}(?!\d)", text)

print("Valid mobile numbers:")
for mobile_number in mobile_numbers:
	print(mobile_number)

'''
Output:
Valid mobile numbers:
9876543210
9123456780
8123456789
'''
