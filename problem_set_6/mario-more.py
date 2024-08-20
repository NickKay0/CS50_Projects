# Get height
GAP_SIZE = 2

height = 0
while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height <= 8:
            break
    except:
        pass

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i + " " * GAP_SIZE + "#" * i)
