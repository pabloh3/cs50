import cs50

g = input("Height: ")
h= int(g)
for i in range(h):
    for j in range(h-(i-1)):
        print(" ", end="")
    for j in range(i+1):
        print("#", end="")
    print("")