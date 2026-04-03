st = input().split()
#print(st)

l = 0
s = 1001

for w in st:
    if len(w) > l: l = len(w)
    if len(w) < s: s = len(w)

print(s, l)
