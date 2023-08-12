from cs50 import get_int

height = get_int("Height: ")

while not (1 <= height <= 8):
    print("Only integers between 1 - 8")
    height = get_int("Height: ")

for i in range(1, height + 1):
    spaces = ' ' * (height - i)
    hashes_left = '#' * i
    hashes_right = '#' * i
    gap = '  '
    print(f"{spaces}{hashes_left}{gap}{hashes_right}")
