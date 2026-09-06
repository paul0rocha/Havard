from cs50 import get_string
from string import ascii_letters

text = get_string("Text: ")

# Count letters
letters = 0
for character in text:
    if character in ascii_letters:
        letters += 1

# Count words
words = len(text.split())

# Count sentences
sentences = 0
for character in text:
    if character in ".!?":
        sentences += 1

# Coleman-Liau index
L = letters * 100 / words
S = sentences * 100 / words

index = 0.0588 * L - 0.296 * S - 15.8

# Print grade
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {round(index)}")
