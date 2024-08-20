text = input("Text: ")
letters, words, sentences = 0, 1, 0

for c in text:
    if c.isalpha():
        letters += 1
    elif c == " ":
        words += 1
    elif c in [".", "?", "!"]:
        sentences += 1

l = letters / words * 100
s = sentences / words * 100
grade = round(0.0588 * l - 0.296 * s - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
