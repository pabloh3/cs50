import cs50

f=0
while (f == 0):
    c = input("How much change do you need?: ")
    d = int(c)
    if d<0:
        f = 0
    else:
        f = 1

coins = [0.25, 0.10, 0.05, 0.01] 
change = []
for i in range(len(coins)):
    a = d//coins[i]
    r = d%coins[i]
    change.append(a)
    d = r

print("{}".format(int(sum(change))))




