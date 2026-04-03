N = int(input())
inarr = []

for i in range(N):
    inarr.append(int(input()))
for i in range(N-1, -1, -1):
    print(inarr[i])
