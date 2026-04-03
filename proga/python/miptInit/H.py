n, m = list(map(int, input().split()))
l = list(map(int, input().split()))
l1 = [0]*len(l)

for i in range(n):
    l1[i-(m%n)] = l[i]

print(*l1)
