#write a program input a sentence  display the number of charecters words vowlels number of occurances of the letter "a" , the sentence in reverse order 

word = "Hello World abcde"

words = word.split()


count = 0
vowel = 0
a = 0
for i in words:
    for j in i:
        count = count + 1
        if j in "aeiouAEIOU":
            vowel = vowel + 1
        if j in "Aa":
            a = a + 1
 
    
    
    
    
print("Number of words =",len(words))
print("Number of Letters =",vowel)
print("Number of Letters =",count)
print("Occurences of 'a' =",a)

